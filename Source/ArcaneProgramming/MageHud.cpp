// Fill out your copyright notice in the Description page of Project Settings.


#include "MageHud.h"

#include "ArcaneGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMageHud::BeginPlay()
{
	Super::BeginPlay();
	AArcaneGameModeBase* GameModeBase = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameModeBase->MageHud = this;
	UIHudInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), UIHud, TEXT("GridMenu"));
	
}

void AMageHud::MenuOn()
{
	if (UIHudInstance)
	{
		UIHudInstance->AddToViewport();
		
	}
}

void AMageHud::MenuOff()
{
	if (UIHudInstance)
	{
		UIHudInstance->RemoveFromViewport();
		
	}
}

