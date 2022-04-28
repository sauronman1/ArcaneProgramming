// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "ConvertSpellToTarget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UConvertSpellToTarget : public UParameterBlock
{
	GENERATED_BODY()
public:
	UConvertSpellToTarget();

	bool TargetFound = false;
	
	UPROPERTY()
	AActor* SpellTarget;
	UPROPERTY(EditAnywhere)
	UTexture2D* ErrorTexture;
	UPROPERTY(EditAnywhere)
	UTexture2D* ParameterTexture;
	UPROPERTY(meta = (Bindwidget))
	UImage* ParameterImage;
	
	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	virtual void SetSpells(USpellBlock* SpellBlock, int Neighbour) override;
	virtual AActor* Target() override; 
};
