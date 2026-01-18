// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ShooterSamCharacter.h"

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create sphere component for collision
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);

	// Create static mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPack::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// If other acotr is ShooterSamCharacter and not an AI, increase health
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("Health Pack overlapped with: %s"), *OtherActor->GetName());

	if (AShooterSamCharacter* ShooterSam = Cast<AShooterSamCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Pack overlapped with ShooterSamCharacter"));
		if (!ShooterSam->bIsAICharacter && ShooterSam->bIsAlive)
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Pack restoring health to ShooterSamCharacter"));
			ShooterSam->CurrentHealth = FMath::Clamp(ShooterSam->CurrentHealth + HealthAmount, 0.0f, ShooterSam->MaxHealth);
			ShooterSam->UpdateHUD();
			// Destroy health pack
			Destroy();
		}
	}
}

