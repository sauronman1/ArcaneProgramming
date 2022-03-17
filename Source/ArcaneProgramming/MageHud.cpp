// Fill out your copyright notice in the Description page of Project Settings.


#include "MageHud.h"

#include "Blueprint/UserWidget.h"

void AMageHud::BeginPlay()
{
	Super::BeginPlay();
	UIHudInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), UIHud, TEXT("GridMenu"));
	if (UIHudInstance)
	{
		UIHudInstance->AddToViewport();
		
	}
}
