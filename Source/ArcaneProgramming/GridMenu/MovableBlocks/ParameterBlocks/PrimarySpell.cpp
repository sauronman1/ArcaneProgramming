// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimarySpell.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"

UPrimarySpell::UPrimarySpell()
{
	ParaType = ParameterType::Primary;
}

void UPrimarySpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		MenuSet = true;
	}
}
