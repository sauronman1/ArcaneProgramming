// Fill out your copyright notice in the Description page of Project Settings.


#include "ParameterBlock.h"

#include "PipeBlock.h"
#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "Kismet/GameplayStatics.h"

void UParameterBlock::UpdateNeighbours()
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
					USpellBlock* TargetBlock = Cast<USpellBlock>(CurrentNode);
					if(TargetBlock != nullptr)
					{
						TargetBlock->UpdateNeighbours();
					}
					
					
				}
			}
			while(PipeBlock != nullptr)
			{

				if(PipeBlock->NextNode == LastPipe)
				{//TODO Turn this to function, to avoid Redundancy
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
					USpellBlock* TargetBlock = Cast<USpellBlock>(CurrentNode);
					if(TargetBlock != nullptr)
					{
						TargetBlock->UpdateNeighbours();
					}
					
					
				}
			}
			
			USpellBlock* TargetBlock = Cast<USpellBlock>(*GridMenu->Slots.Find(Neighbour));
			if(TargetBlock != nullptr)
			{
				TargetBlock->UpdateNeighbours();
			}
		}
	}
}

void UParameterBlock::ClickAndDrop()
{
	if(OccupiedSlot != nullptr)
	{
		GridMenu->SetSlotInArray(OccupiedSlot, OccupiedSlot->SlotID, true);
		OccupiedSlot->UniGrid->RemoveChild(this);
		OccupiedSlot->SlotImage->SetVisibility(ESlateVisibility::Visible);
		OccupiedSlot = nullptr;

		UPipeBlock* PipeBlock = Cast<UPipeBlock>(this);
		if(PipeBlock != nullptr)
		{
			PipeBlock->NextNode = nullptr;
			PipeBlock->PreviousNode = nullptr;
		}
		//TODO if needed, make an invisible background widget to handle anything dropped outside the menu
	}
	
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;
	GridMenu->SelectedBlock = CreateWidget(GetWorld(), SpellBlueprint);
}


