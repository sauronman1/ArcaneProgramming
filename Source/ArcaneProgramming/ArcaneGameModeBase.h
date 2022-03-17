// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridMenu/GridMenu.h"

#include "ArcaneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API AArcaneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
	
	UPROPERTY()
	UGridMenu* GridMenu;
};
