// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "LookAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API ULookAtTarget : public UParameterBlock
{
	GENERATED_BODY()
public:

	ULookAtTarget();
	virtual AActor* Target() override;

private:
	UPROPERTY(EditAnywhere, Category="Force Variables")
	float TraceDistance = 1000.f;
	UPROPERTY(EditAnywhere, Category="Force Variables")
	float ImpulseForce = 50.f;

	virtual void NativeConstruct() override;
	
};
