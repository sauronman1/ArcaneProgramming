// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "PlayerTarget.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UPlayerTarget : public UParameterBlock
{
	GENERATED_BODY()
public:

	UPlayerTarget();
	
	virtual AActor* Target() override;

private:
	virtual void NativeConstruct() override;

};
