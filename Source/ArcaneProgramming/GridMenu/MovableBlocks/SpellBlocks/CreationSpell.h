// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"

#include "CreationSpell.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UCreationSpell : public USpellBlock
{
	GENERATED_BODY()

public:

	VectorType DirectionToSpawnRelativeToSpawner = VectorType::None;
	
private:
	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	virtual void ActivateSpell() override;
};
