// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ShooterSamCharacter.h"

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
//void AHealthPack::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AHealthPack::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// If other acotr is ShooterSamCharacter and not an AI, increase health
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AShooterSamCharacter* ShooterSam = Cast<AShooterSamCharacter>(OtherActor))
	{
		if (!ShooterSam->bIsAICharacter && ShooterSam->bIsAlive && ShooterSam->CurrentHealth < ShooterSam->MaxHealth)
		{
			ShooterSam->Heal(HealthAmount);
			// Destroy health pack
			Destroy();
		}
	}
}

