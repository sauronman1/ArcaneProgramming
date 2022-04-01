// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "ConvertSpellToTarget.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UConvertSpellToTarget : public UParameterBlock
{
	GENERATED_BODY()
public:
	UConvertSpellToTarget();
	
	UPROPERTY()
	AActor* SpellTarget;

	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	virtual AActor* Target() override; 
};
