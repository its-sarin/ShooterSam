// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NiagaraComponent.h"
#include "ShooterSamCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class AGun;
class AShooterSamPlayerController;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AShooterSamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ShootAction;

	/** Zoom Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ZoomAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

public:

	/** Constructor */
	AShooterSamCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for zoom input */
	void Zoom(const FInputActionValue& Value);

	/** Called for sprint input */
	void Sprint(const FInputActionValue& Value);

public:
	virtual void Tick(float DeltaTime) override;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Handles shoot input */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void Shoot();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category="Health")
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsAlive = true;

	UPROPERTY(EditAnywhere)
	bool bIsAICharacter = false;

	/** Gun Actor to spawn */
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AGun> GunClass;
	
	UFUNCTION()
	void HandleTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	void UpdateHUD();

	UPROPERTY(EditAnywhere)
	float ZoomedFOV = 60.0f;

	UPROPERTY(EditAnywhere)
	float DefaultFOV = 90.0f;

	UPROPERTY(EditAnywhere)
	float ZoomInSensitivity = 0.5f;

	UPROPERTY(EditAnywhere)
	float DefaultSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintMaxWalkSpeed = 550.0f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* HealingEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HealingSound;

	void Heal(float HealAmount);

private:
	AGun* Gun;

	bool bShouldZoomIn = false;
	bool bShouldZoomOut = false;
	bool bIsSprinting = false;
	float DefaultMaxWalkSpeed;

	FVector2D MovementVector;

	void StartSprint();
	void StopSprint();

};
