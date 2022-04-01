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
	UPROPERTY()
	FVector Direction;

	VectorType VType = VectorType::None;

	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	virtual void ActivateSpell() override;
};
