// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBlock.h"
#include "Components/CheckBox.h"

#include "GravitySpell.generated.h"

class UEditableText;

UCLASS()
class ARCANEPROGRAMMING_API UGravitySpell : public USpellBlock
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void SetParameters(UParameterBlock* ParameterBlock, int Neighbour) override;
	virtual void ActivateSpell() override;
private:
	UPROPERTY(meta = (BindWidget))
	UEditableText* SpellDurationBox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* RemoveGravityBox;

	bool RemoveGravity;
	
	UFUNCTION()
	void SetSpellDuration(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
	void SetGravity(bool CheckedState);
};
