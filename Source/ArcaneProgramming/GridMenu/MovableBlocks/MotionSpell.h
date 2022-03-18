// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBlock.h"
#include "MotionSpell.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UMotionSpell : public USpellBlock
{
	GENERATED_BODY()
	public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SpellBlueprint;
	UPROPERTY()
	UUserWidget* SpellBlueprintInstance;
	UPROPERTY()
	UGridMenu* GridMenu;

	UPROPERTY()
	AActor* Target;
	UPROPERTY()
	FVector Direction;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void UpdateNeighbours() override;
};
