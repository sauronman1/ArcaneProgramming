// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UUserWidget* WidgetReference;
	UPROPERTY(EditAnywhere)
	FVector2D DragOffset;
	
};
