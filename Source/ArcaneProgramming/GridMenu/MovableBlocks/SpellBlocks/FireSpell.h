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

	
private:
	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	virtual void ActivateSpell() override;

	
};
