// Fill out your copyright notice in the Description page of Project Settings.


#include "MotionSpell.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
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



void UMotionSpell::UpdateNeighbours()
{
	TArray<int> Neighbours = {OccupiedSlot->Right, OccupiedSlot->Up, OccupiedSlot->Left, OccupiedSlot->Down};

	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UParameterBlock* TargetBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
			if(TargetBlock != nullptr)
			{
				if(TargetBlock->ParaType == ParameterType::Actor)
				{
					Target = TargetBlock->Target();
				}
				if(TargetBlock->ParaType == ParameterType::Direction)
				{
					Direction = TargetBlock->Direction();
					Amplifier = TargetBlock->Amplifier;
				}
				if(TargetBlock->ParaType == ParameterType::VectorEnum)
				{
					VType = TargetBlock->VType;
					Amplifier = TargetBlock->Amplifier;
				}
			}

			
		}

		
	}

	if(Target == nullptr)
	{
		//Change to Error material
	}
	
}

void UMotionSpell::ActivateSpell()
{
	UpdateNeighbours();

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








