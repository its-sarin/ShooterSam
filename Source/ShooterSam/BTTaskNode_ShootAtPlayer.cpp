// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ShootAtPlayer.h"
#include "ShooterAI.h"
#include "ShooterSamCharacter.h" // FIX: Include the full class definition

UBTTaskNode_ShootAtPlayer::UBTTaskNode_ShootAtPlayer()
{
	NodeName = TEXT("Shoot At Player");
}

EBTNodeResult::Type UBTTaskNode_ShootAtPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());

	if (OwnerController)
	{
		AShooterSamCharacter* OwnerCharacter = OwnerController->MyCharacter;
		AShooterSamCharacter* PlayerCharacter = OwnerController->PlayerCharacter;

		if (OwnerCharacter && PlayerCharacter && PlayerCharacter->bIsAlive)
		{
			OwnerCharacter->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
