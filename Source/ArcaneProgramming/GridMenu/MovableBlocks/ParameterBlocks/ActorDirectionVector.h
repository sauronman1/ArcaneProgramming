// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "ActorDirectionVector.generated.h"

UCLASS()
class ARCANEPROGRAMMING_API UActorDirectionVector : public UParameterBlock
{
	GENERATED_BODY()
	
public:
	UActorDirectionVector();

	virtual VectorType VecType() override;

private:
	UPROPERTY(meta = (BindWidget))
	UEditableText* AmplifierBox;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetAmplifier(const FText& Text, ETextCommit::Type type);
};
