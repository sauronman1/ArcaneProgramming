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
	virtual void NativeConstruct() override;
	virtual void SetParameters(UParameterBlock* ParameterBlock, int Neighbour) override;
	virtual void ActivateSpell() override;
	
private:
	VectorType DirectionToSpawnRelativeToSpawner = VectorType::None;

	UPROPERTY(meta = (BindWidget))
	UEditableText* SpellDurationBox;
	
	UFUNCTION()
	void SetSpellDuration(const FText& Text, ETextCommit::Type type);
};
