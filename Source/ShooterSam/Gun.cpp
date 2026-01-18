// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAI.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlashParticleSystem->SetupAttachment(GunMesh);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	MuzzleFlashParticleSystem->Deactivate();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (OwnerController)
	{
		MuzzleFlashParticleSystem->Activate(true);
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ShootSound,
			GetActorLocation()
		);

		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);	

		FHitResult HitResult;
		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

		// Add deviation for inaccuracy if OwnerController is ShooterAI
		if (Cast<AShooterAI>(OwnerController)) 
		{
			FRotator DeviationRotator = FRotator(
				FMath::FRandRange(-AIShotDeviationAngle, AIShotDeviationAngle),
				FMath::FRandRange(-AIShotDeviationAngle, AIShotDeviationAngle),
				0.0f
			);
			FVector DeviatedDirection = DeviationRotator.RotateVector(ViewPointRotation.Vector());
			EndLocation = ViewPointLocation + DeviatedDirection * MaxRange;
		}

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		bool IsHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ViewPointLocation,
			EndLocation,
			ECollisionChannel::ECC_GameTraceChannel1,
			Params
		);

		if (IsHit)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				ImpactSound,
				HitResult.ImpactPoint
			);

			if (AActor* HitActor = HitResult.GetActor())
			{
				if (HitActor->CanBeDamaged() && HitActorParticleSystem)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						HitActorParticleSystem,
						HitResult.ImpactPoint,
						HitResult.ImpactNormal.Rotation()
					);
				}
				else
				{
					if (HitWorldParticleSystem)
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(),
							HitWorldParticleSystem,
							HitResult.ImpactPoint,
							HitResult.ImpactNormal.Rotation()
						);
					}
				}

				UGameplayStatics::ApplyDamage(
					HitActor,
					BulletDamage,
					OwnerController,
					this,
					UDamageType::StaticClass()
				);
			}
			else
			{				
				if (HitWorldParticleSystem)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						HitWorldParticleSystem,
						HitResult.ImpactPoint,
						HitResult.ImpactNormal.Rotation()
					);
				}
			}
		}
	}
}

