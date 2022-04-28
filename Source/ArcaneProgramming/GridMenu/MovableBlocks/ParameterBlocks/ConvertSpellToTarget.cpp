// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvertSpellToTarget.h"

#include "PipeBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"

UConvertSpellToTarget::UConvertSpellToTarget()
{
	ParaType = ParameterType::Converter;
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
	TargetFound = false;

	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UPipeBlock* PipeBlock = Cast<UPipeBlock>(*GridMenu->Slots.Find(Neighbour));
			if(PipeBlock != nullptr)
			{
				for (auto PipeNeighbour : PipeBlock->Neighbours)
				{
					if(PipeNeighbour == SlotID)
						SetSpells(PipeBlock->HeadNode, Neighbour);

				}
			}
			
			SetSpells(Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour)), Neighbour);
			
		}
	}

	GridMenu->ShowManaCost();
}

void UConvertSpellToTarget::SetSpells(USpellBlock* SpellBlock, int Neighbour)
{
	if(SpellBlock != nullptr && SpellBlock->Targetable && Neighbour == OccupiedSlot->Left)
	{
		SpellTarget = SpellBlock->SpellTarget;
		TargetFound = true;
		SpellBlock->UpdateNeighbours();
	}

	if(SpellBlock != nullptr)
	{
		SpellBlock->UpdateNeighbours();
	}

	if(!TargetFound)
		ParameterImage->SetBrushFromTexture(ErrorTexture);
	else
		ParameterImage->SetBrushFromTexture(ParameterTexture);

	
}


AActor* UConvertSpellToTarget::Target()
{
	return SpellTarget;
}
