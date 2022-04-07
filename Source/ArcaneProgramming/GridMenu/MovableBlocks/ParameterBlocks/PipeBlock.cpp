// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeBlock.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"

void UPipeBlock::UpdateNeighbours()
{
	TArray<int> Neighbours = {};

	if(HasEast)
		Neighbours.Add(OccupiedSlot->Right);
	if(HasWest)
		Neighbours.Add(OccupiedSlot->Left);
	if(HasNorth)
		Neighbours.Add(OccupiedSlot->Up);
	if(HasSouth)
		Neighbours.Add(OccupiedSlot->Down);
	
	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UGridBlock* TargetBlock = Cast<UGridBlock>(*GridMenu->Slots.Find(Neighbour));
			if(TargetBlock == nullptr)
			{
				UParameterBlock* ParameterBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
				if(ParameterBlock != nullptr)
					ParameterBlock->UpdateNeighbours();
				
				USpellBlock* SpellBlock = Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour));
				if(SpellBlock != nullptr)
					SpellBlock->UpdateNeighbours();
				
				if(PreviousNode == nullptr)
					PreviousNode = TargetBlock;
				else
					NextNode = TargetBlock;
				
			}
		}
	}
}
