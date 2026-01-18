// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"

void UHUDWidget::SetHealthBarPercent(float NewPercent)
{
	if (NewPercent <= 1.f && NewPercent >= 0.f && PlayerHealthBar)
	{
		PlayerHealthBar->SetPercent(NewPercent);
	}
}
