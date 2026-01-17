// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "ShooterSamCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	check(PlayerPawn);

	if (EnemyAIBehaviorTree)
	{
		RunBehaviorTree(EnemyAIBehaviorTree);
	}
}

void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
}

void AShooterAI::StartBehaviorTree(AShooterSamCharacter* Player)
{
	if (EnemyAIBehaviorTree)
	{
		MyCharacter = Cast<AShooterSamCharacter>(GetPawn());

		if (Player)
		{
			PlayerCharacter = Player;
		}				

		RunBehaviorTree(EnemyAIBehaviorTree);

		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp && MyCharacter && PlayerCharacter)
		{
			BlackboardComp->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());
		}
	}
}
