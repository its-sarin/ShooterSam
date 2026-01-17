// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ShootAtPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAM_API UBTTaskNode_ShootAtPlayer : public UBTTaskNode
{
	GENERATED_BODY()


public:
	UBTTaskNode_ShootAtPlayer();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
