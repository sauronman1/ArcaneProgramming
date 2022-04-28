// Fill out your copyright notice in the Description page of Project Settings.


#include "MotionSpell.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/PipeBlock.h"
#include "ArcaneProgramming/Player/MagePlayer.h"
#include "ArcaneProgramming/Spells/MotionSpellComponent.h"
#include "Kismet/GameplayStatics.h"

void UMotionSpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		MenuSet = true;
	}
}





void UMotionSpell::SetParameters(UParameterBlock* ParameterBlock, int Neighbour)
{
	if(ParameterBlock != nullptr)
	{
		if(ParameterBlock->ParaType == ParameterType::Actor)
		{
			Target = ParameterBlock->Target();
		}
		if(ParameterBlock->ParaType == ParameterType::Direction)
		{
			Direction = ParameterBlock->Direction();
			Amplifier = ParameterBlock->Amplifier;
		}
		if(ParameterBlock->ParaType == ParameterType::VectorEnum)
		{
			VType = ParameterBlock->VType;
			Amplifier = ParameterBlock->Amplifier;
		}
		if(ParameterBlock->ParaType == ParameterType::Primary && Neighbour == OccupiedSlot->Down)
			IsPrimary = true;
		if(ParameterBlock->ParaType == ParameterType::Converter && Neighbour != OccupiedSlot->Right)
            Target = ParameterBlock->Target();
	}
}


void UMotionSpell::ActivateSpell()
{
	Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu->UpdateNeigboursOnAllNodes();

	if(Target == nullptr)
	{
		return;
	}

	UMotionSpellComponent* SpellMotionComponent = Target->FindComponentByClass<UMotionSpellComponent>();
	if(SpellMotionComponent == nullptr)
	{
		SpellMotionComponent = NewObject<UMotionSpellComponent>(Target, UMotionSpellComponent::StaticClass());
		SpellMotionComponent->RegisterComponent();
	}
	
	SpellMotionComponent->AddMotion(Direction, Amplifier, VType);
}








