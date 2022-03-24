// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CustomButton.generated.h"

UCLASS()
class ARCANEPROGRAMMING_API UCustomButton : public UButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
    UParticleSystemComponent* PSComponent;
	
};
