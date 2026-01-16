// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), FoundEnemies);

	for (AActor* EnemyActor : FoundEnemies)
	{
		AShooterAI* EnemyAI = Cast<AShooterAI>(EnemyActor->GetInstigatorController());
		if (EnemyAI)
		{
			EnemyAI->StartBehaviorTree(Player);
		}
	}

}
