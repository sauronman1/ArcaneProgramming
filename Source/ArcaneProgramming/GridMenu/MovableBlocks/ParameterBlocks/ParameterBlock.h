// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParameterBlock.generated.h"

class UCustomButton;
class UDragWidget;
class UGridBlock;
class UGridMenu;

UENUM()
enum ParameterType
{
	Direction,
	VectorEnum,
	Position,
	Actor,
	
};

UENUM(BlueprintType)
enum VectorType
{
	None,
	ActorUpVector,
	ActorRightVector,
	ActorForwardVector,
	ActorPosition ,
};

UCLASS(Abstract)
class ARCANEPROGRAMMING_API UParameterBlock : public UUserWidget
{
	GENERATED_BODY()

public:	
	ParameterType ParaType;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<VectorType> VType;
	
	bool PlacedOnGrid = false;
	bool HasActivated = false;
	bool MenuSet = false;
	int SlotID;

	UPROPERTY()
	UGridBlock* OccupiedSlot;	
	UPROPERTY()
	UGridMenu* GridMenu;
	UPROPERTY()
	UUserWidget* SpellBlueprintInstance;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SpellBlueprint;
	UPROPERTY(meta = (BindWidget))
	UCustomButton* CustomParameterButton;
	
	UDragWidget* DragOperator(UDragWidget* DragOperation);
	
	virtual void UpdateNeighbours();
	virtual FVector Position() {return FVector::ZeroVector;}
	virtual FVector Direction() {return FVector::ZeroVector;}
	virtual VectorType VecType() {return VectorType::ActorUpVector;}
	virtual AActor* Target() {return nullptr;}

	UFUNCTION()
	void ClickAndDrop();
};
