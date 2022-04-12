// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"

#include "ParameterBlock.generated.h"

class USpellBlock;
class UCustomButton;
class UDragWidget;
class UGridBlock;
class UGridMenu;

UENUM()
enum ParameterType
{
	Pipe,
	Direction,
	VectorEnum,
	Position,
	Actor,
	Primary,

};

UENUM(BlueprintType)
enum VectorType
{
	None,
	ActorUpVector,
	ActorRightVector,
	ActorForwardVector,
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
	float Amplifier;

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
		
	virtual void UpdateNeighbours();
	virtual void SetSpells(USpellBlock* SpellBlock, int Neighbour){}
	virtual FVector Position() {return FVector::ZeroVector;}
	virtual FVector Direction() {return FVector::ZeroVector;}
	virtual VectorType VecType() {return VectorType::ActorUpVector;}
	virtual AActor* Target() {return nullptr;}

	UFUNCTION()
	void ClickAndDrop();
};
