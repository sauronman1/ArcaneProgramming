// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParameterBlock.generated.h"

class UDragWidget;
class UGridBlock;
class UGridMenu;

enum ParameterType
{
	Vector,
	Actor,
	
};

UCLASS(Abstract)
class ARCANEPROGRAMMING_API UParameterBlock : public UUserWidget
{
	GENERATED_BODY()

public:	
	ParameterType ParaType;

	bool PlacedOnGrid = false;
	bool HasActivated = false;
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
	virtual void UpdateNeighbours();
	
	virtual FVector Vector() {return FVector::ZeroVector;}
	virtual AActor* Target() {return nullptr;}
};
