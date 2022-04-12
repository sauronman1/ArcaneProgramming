// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvertSpellToTarget.h"

#include "PipeBlock.h"
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
	UPipeBlock* LastPipe = nullptr;
	UWidget* CurrentNode = nullptr;
	
	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UPipeBlock* PipeBlock = Cast<UPipeBlock>(*GridMenu->Slots.Find(Neighbour));
			if(PipeBlock != nullptr)
			{
				PipeBlock->SetNextAndPrevious(this);
				if(PipeBlock->NextNode == this)
				{
					CurrentNode = PipeBlock->PreviousNode;
					PipeBlock = Cast<UPipeBlock>(PipeBlock->PreviousNode);
				}
				else
				{
					CurrentNode = PipeBlock->NextNode;
					PipeBlock = Cast<UPipeBlock>(PipeBlock->NextNode);
				}

				LastPipe = PipeBlock;

				if(CurrentNode != nullptr)
				{
					SetSpells(Cast<USpellBlock>(CurrentNode), Neighbour);
					
				}
			}
			while(PipeBlock != nullptr)
			{

				if(PipeBlock->NextNode == LastPipe)
				{
					PipeBlock = Cast<UPipeBlock>(PipeBlock->PreviousNode);
					if(PipeBlock == nullptr)
					{
						CurrentNode = LastPipe->PreviousNode;
					}
				}
				else
				{
					PipeBlock = Cast<UPipeBlock>(PipeBlock->NextNode);
					if(PipeBlock == nullptr)
					{
						CurrentNode = LastPipe->NextNode;
					}
				}

				LastPipe = PipeBlock;

				if(CurrentNode != nullptr)
				{
					SetSpells(Cast<USpellBlock>(CurrentNode), Neighbour);
					
				}
			}
			
			SetSpells(Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour)), Neighbour);
			
		}
	}
}

void UConvertSpellToTarget::SetSpells(USpellBlock* SpellBlock, int Neighbour)
{
	if(SpellBlock != nullptr && SpellBlock->Targetable)
	{
		SpellTarget = SpellBlock->SpellTarget;
		SpellBlock->UpdateNeighbours();
	}
	else if(SpellBlock != nullptr)
	{
		SpellBlock->UpdateNeighbours();
	}
}


AActor* UConvertSpellToTarget::Target()
{
	return SpellTarget;
}
