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
//TODO Might still be buggy

void UPipeBlock::UpdateNeighbours()
{
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
			//Anything that isn't a GridBlock will be set as neighbours
			UGridBlock* GridBlock = Cast<UGridBlock>(*GridMenu->Slots.Find(Neighbour));
			if(GridBlock == nullptr)
				SetNextAndPrevious(*GridMenu->Slots.Find(Neighbour));
			
		}
	}
	
	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UParameterBlock* ParameterBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
			if(ParameterBlock != nullptr && Cast<UPipeBlock>(*GridMenu->Slots.Find(Neighbour)) == nullptr)
			{
				SetTailForAll(ParameterBlock);
			}
				
			USpellBlock* SpellBlock = Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour));
			if(SpellBlock != nullptr)
			{
				SetHeadForAll(SpellBlock);
			}

			
		}
	}

	
}

void UPipeBlock::SetNextAndPrevious(UWidget* TargetBlock)
{
	UPipeBlock* PipeBlock = Cast<UPipeBlock>(TargetBlock);

	if(PipeBlock == nullptr)
	{
		return;
	}

	if(PreviousNode == PipeBlock || NextNode == PipeBlock)
	{
		return;
	}
	
	if(PreviousNode == nullptr && NextNode != TargetBlock && PipeBlock->PreviousNode != this)
	{
		PreviousNode = PipeBlock;
		PipeBlock->NextNode = this;
		PipeBlock->UpdateNeighbours();
	}
	// if(NextNode == nullptr && PreviousNode != TargetBlock  && PipeBlock->NextNode != this)
	// {
	// 	NextNode = PipeBlock;
	// }
}

void UPipeBlock::SetHeadForAll(USpellBlock* TargetBlock)
{
	HeadNode = TargetBlock;
	UPipeBlock* CurrentBlock = nullptr;

	CurrentBlock = Cast<UPipeBlock>(PreviousNode);
	while (CurrentBlock != nullptr)
	{
		CurrentBlock->HeadNode = TargetBlock;
		CurrentBlock = Cast<UPipeBlock>(CurrentBlock->PreviousNode);
	}

	CurrentBlock = Cast<UPipeBlock>(NextNode);
	while (CurrentBlock != nullptr)
	{
		CurrentBlock->HeadNode = TargetBlock;
		CurrentBlock = Cast<UPipeBlock>(CurrentBlock->NextNode);
	}
	
	
	
}

void UPipeBlock::SetTailForAll(UParameterBlock* TargetBlock)
{

	TailNode = TargetBlock;
	UPipeBlock* CurrentBlock = nullptr;

	CurrentBlock = Cast<UPipeBlock>(PreviousNode);
	while (CurrentBlock != nullptr)
	{
		CurrentBlock->TailNode = TargetBlock;
		CurrentBlock = Cast<UPipeBlock>(CurrentBlock->PreviousNode);
	}

	CurrentBlock = Cast<UPipeBlock>(NextNode);
	while (CurrentBlock != nullptr)
	{
		CurrentBlock->TailNode = TargetBlock;
		CurrentBlock = Cast<UPipeBlock>(CurrentBlock->NextNode);
	}
	
	
}


