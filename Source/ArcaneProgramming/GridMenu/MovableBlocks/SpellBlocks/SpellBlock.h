// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ArcaneProgramming/GridMenu/DragWidget.h"
#include "Blueprint/UserWidget.h"
#include "SpellBlock.generated.h"

class UGridBlock;
class UGridMenu;

UCLASS(Abstract)
class ARCANEPROGRAMMING_API USpellBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	bool PlacedOnGrid = false;
	bool HasActivated = false;
	bool Debbuged = false;
	int SlotID;

	UPROPERTY()
	UGridBlock* OccupiedSlot;	
	UPROPERTY()
	UGridMenu* GridMenu;
	UPROPERTY()
	UUserWidget* SpellBlueprintInstance;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SpellBlueprint;
	
	UDragWidget* DragOperator(UDragWidget* DragOperation);
	virtual void UpdateNeighbours(){}
	virtual void ActivateSpell() PURE_VIRTUAL(USpellBlock);
};
