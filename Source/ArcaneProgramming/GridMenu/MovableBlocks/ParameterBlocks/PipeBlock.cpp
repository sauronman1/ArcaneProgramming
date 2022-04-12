// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeBlock.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"

void UPipeBlock::NativeConstruct()
{
	ParaType = ParameterType::Pipe;
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		MenuSet = true;
	}
}


void UPipeBlock::UpdateNeighbours()
{
	TArray<int> Neighbours;
	Neighbours.SetNum(4);

	 if(HasEast)
	 	Neighbours[0] = OccupiedSlot->Right;
	 if(HasWest)
	 	Neighbours[1] = OccupiedSlot->Left;
	 if(HasNorth)
	 	Neighbours[2] = OccupiedSlot->Up;
	 if(HasSouth)
	 	Neighbours[3] = OccupiedSlot->Down;
	
	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UParameterBlock* ParameterBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
			if(ParameterBlock != nullptr && Cast<UPipeBlock>(*GridMenu->Slots.Find(Neighbour)) == nullptr)
				ParameterBlock->UpdateNeighbours();
				
			USpellBlock* SpellBlock = Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour));
			if(SpellBlock != nullptr)
				SpellBlock->UpdateNeighbours();

			UGridBlock* GridBlock = Cast<UGridBlock>(*GridMenu->Slots.Find(Neighbour));
			if(GridBlock == nullptr)
				SetNextAndPrevious(*GridMenu->Slots.Find(Neighbour));
		}
	}

	
}

void UPipeBlock::SetNextAndPrevious(UWidget* TargetBlock)
{
	if(PreviousNode == nullptr || PreviousNode == TargetBlock)
		PreviousNode = TargetBlock;
	else 
		NextNode = TargetBlock;
}
