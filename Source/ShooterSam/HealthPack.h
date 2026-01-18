// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class SHOOTERSAM_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// Amount of health to restore
	UPROPERTY(EditAnywhere, Category = "Health")
	float HealthAmount = 25.0f;

	// Function to handle overlap events
	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
