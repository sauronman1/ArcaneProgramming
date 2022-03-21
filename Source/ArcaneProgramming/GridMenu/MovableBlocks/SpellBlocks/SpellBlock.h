// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "Blueprint/UserWidget.h"
#include "SpellBlock.generated.h"

class UGridBlock;

UCLASS(Abstract)
class ARCANEPROGRAMMING_API USpellBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	bool PlacedOnGrid = false;
	bool HasActivated = false;
	int SlotID;

	UPROPERTY()
	UGridBlock* OccupiedSlot;	
	
	virtual void UpdateNeighbours() PURE_VIRTUAL(USpellBlock);
	virtual void ActivateSpell() PURE_VIRTUAL(USpellBlock);
};
