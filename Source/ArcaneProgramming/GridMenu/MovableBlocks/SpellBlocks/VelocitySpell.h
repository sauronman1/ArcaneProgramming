// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "VelocitySpell.generated.h"

UCLASS()
class ARCANEPROGRAMMING_API UVelocitySpell : public USpellBlock
{
	GENERATED_BODY()
	

	virtual void NativeConstruct() override;
	virtual void SetParameters(UParameterBlock* ParameterBlock, int Neighbour) override;
	virtual void ActivateSpell() override;

private:
	UPROPERTY(meta = (BindWidget))
	UEditableText* SpellDurationBox;
	UPROPERTY()
	FVector Direction;
	
	VectorType VType = VectorType::None;

	UFUNCTION()
	void SetSpellDuration(const FText& Text, ETextCommit::Type type);
};
