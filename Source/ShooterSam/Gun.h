// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	AController* OwnerController;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.f;

	UPROPERTY(EditAnywhere)
	float BulletDamage = 10.f;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* HitWorldParticleSystem;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* HitActorParticleSystem;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AIShotDeviationAngle = 3.5f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ImpactSound;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* MuzzleFlashParticleSystem;


};
