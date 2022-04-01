// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "PrimarySpell.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UPrimarySpell : public UParameterBlock
{
	GENERATED_BODY()
public:
	UPrimarySpell();
private:
	virtual void NativeConstruct() override;

};
