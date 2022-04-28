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
	CrosshairHudInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), CrosshairHud, TEXT("Crosshair"));
	if (CrosshairHudInstance)
	{
		CrosshairHudInstance->AddToViewport();
	}
}

void AMageHud::MenuOn()
{
	if (UIHudInstance && CrosshairHudInstance)
	{
		UIHudInstance->AddToViewport();
		CrosshairHudInstance->RemoveFromViewport();
	}
}

void AMageHud::MenuOff()
{
	if (UIHudInstance && CrosshairHudInstance)
	{
		UIHudInstance->RemoveFromViewport();
		CrosshairHudInstance->AddToViewport();

	}
}

