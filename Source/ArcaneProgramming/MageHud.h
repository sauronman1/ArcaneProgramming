// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MageHud.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API AMageHud : public AHUD
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> UIHud;
	UPROPERTY()
	UUserWidget* UIHudInstance;

	void MenuOn();
	void MenuOff();
};
