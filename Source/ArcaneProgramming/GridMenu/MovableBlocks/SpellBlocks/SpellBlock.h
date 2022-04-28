// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "SpellBlock.generated.h"

class UParameterBlock;
class UCustomButton;
class UGridBlock;
class UGridMenu;

UCLASS(Abstract)
class ARCANEPROGRAMMING_API USpellBlock : public UUserWidget
{
	//Todo Attempt to merge Parameter and Spell Blocks to Movable blocks

	GENERATED_BODY()
public:
	bool PlacedOnGrid = false;
	bool MenuSet = false;
	bool IsPrimary = false;
	bool TargetFound = false;
	int SlotID;
	float Amplifier;
	float SpellDuration;
	
	UPROPERTY(EditAnywhere)
	bool Targetable = false;
	UPROPERTY()
	UGridBlock* OccupiedSlot;	
	UPROPERTY()
	UGridMenu* GridMenu;
	UPROPERTY()
	UUserWidget* SpellBlueprintInstance;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SpellBlueprint;
	UPROPERTY(EditAnywhere)
	UTexture2D* ErrorTexture;
	UPROPERTY(EditAnywhere)
	UTexture2D* SpellTexture;
	UPROPERTY(meta = (BindWidget))
	UCustomButton* CustomButton;
	UPROPERTY(meta = (BindWidget))
	UImage* SpellImage;
	
	UPROPERTY()
	AActor* Target;
	UPROPERTY()
	AActor* SpellTarget;
		
	virtual void UpdateNeighbours();
	virtual void VerifySpell(UParameterBlock* ParameterBlock);
	virtual void SetParameters(UParameterBlock* ParameterBlock, int Neighbour){}
	virtual void ActivateSpell() PURE_VIRTUAL(USpellBlock);
	
	UFUNCTION()
    void ClickAndDrop();
};
