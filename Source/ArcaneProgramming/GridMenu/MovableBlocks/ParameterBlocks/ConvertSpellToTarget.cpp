// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvertSpellToTarget.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"

UConvertSpellToTarget::UConvertSpellToTarget()
{
	ParaType = ParameterType::Actor;
}

void UConvertSpellToTarget::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		MenuSet = true;
	}
}

void UConvertSpellToTarget::UpdateNeighbours()
{
	TArray<int> Neighbours = {OccupiedSlot->Right, OccupiedSlot->Up, OccupiedSlot->Left, OccupiedSlot->Down};

	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			USpellBlock* SpellBlock = Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour));
			if(SpellBlock != nullptr && SpellBlock->Targetable)
			{
				SpellTarget = SpellBlock->SpellTarget;
				SpellBlock->UpdateNeighbours();
			}
			else if(SpellBlock != nullptr)
			{
				SpellBlock->UpdateNeighbours();
			}

			// UParameterBlock* ParameterBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
			// if(ParameterBlock != nullptr)
			// 	ParameterBlock->UpdateNeighbours();
			
		}
	}
}


AActor* UConvertSpellToTarget::Target()
{
	return SpellTarget;
}
