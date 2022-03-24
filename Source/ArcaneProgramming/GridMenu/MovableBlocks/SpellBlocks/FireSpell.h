// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBlock.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"

#include "FireSpell.generated.h"

class UParticleSystemComponent;

UCLASS()
class ARCANEPROGRAMMING_API UFireSpell : public USpellBlock
{
	GENERATED_BODY()
public:
	UPROPERTY()
	AActor* Target;
	UPROPERTY(meta = (BindWidget))
	UCustomButton* FireButton;
	
private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void UpdateNeighbours() override;
	virtual void ActivateSpell() override;
};
