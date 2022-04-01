// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSpell.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/Spells/FireSpellComponent.h"
#include "Particles/ParticleSystemComponent.h"

void UFireSpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		MenuSet = true;
	}
}

void UFireSpell::UpdateNeighbours()
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
				
			}

			
		}

		
	}

	if(Target == nullptr)
	{
		//Change to Error material
	}
	
}

void UFireSpell::ActivateSpell()
{
	UpdateNeighbours();
	
	if(Target == nullptr)
	{
		return;
	}

	UFireSpellComponent* FireSpellComponent = Target->FindComponentByClass<UFireSpellComponent>();
	if(FireSpellComponent == nullptr)
	{
		FireSpellComponent = NewObject<UFireSpellComponent>(Target, UFireSpellComponent::StaticClass());
		FireSpellComponent->RegisterComponent();
		FireSpellComponent->PSComponent = CustomButton->PSComponent;
	}
	else
	{
		FireSpellComponent->Activate();	
	}

	
	
	FireSpellComponent->IncinerateTarget();
}


