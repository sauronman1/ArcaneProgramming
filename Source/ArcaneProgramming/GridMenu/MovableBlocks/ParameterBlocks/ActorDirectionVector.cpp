// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorDirectionVector.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"

UActorDirectionVector::UActorDirectionVector()
{
	ParaType = ParameterType::VectorEnum;
	VType = VectorType::ActorUpVector;
}

void UActorDirectionVector::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		MenuSet = true;
	}
}

VectorType UActorDirectionVector::VecType()
{
	return VType;
}