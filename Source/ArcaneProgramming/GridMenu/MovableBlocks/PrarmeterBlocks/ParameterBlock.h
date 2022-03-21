// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParameterBlock.generated.h"

enum ParameterType
{
	Vector,
	Actor,
	
};

UCLASS(Abstract)
class ARCANEPROGRAMMING_API UParameterBlock : public UUserWidget
{
	GENERATED_BODY()

	ParameterType ParaType;
	
	virtual FVector Vector() PURE_VIRTUAL(UParameterBlock::Vector, return FVector::ZeroVector;);
	virtual AActor* Target() PURE_VIRTUAL(UParameterBlock::Target, return nullptr;);
};
