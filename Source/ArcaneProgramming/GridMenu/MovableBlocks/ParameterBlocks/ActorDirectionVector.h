// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "ActorDirectionVector.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UActorDirectionVector : public UParameterBlock
{
	GENERATED_BODY()
	
public:
	UActorDirectionVector();

	virtual VectorType VecType() override;

private:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
