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
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
