// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBlock.h" 

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/PipeBlock.h"
#include "Kismet/GameplayStatics.h"

void USpellBlock::ClickAndDrop()
{
	if(OccupiedSlot != nullptr)
	{
		GridMenu->SetSlotInArray(OccupiedSlot, OccupiedSlot->SlotID, true);
		OccupiedSlot->UniGrid->RemoveChild(this);
		OccupiedSlot->SlotImage->SetVisibility(ESlateVisibility::Visible);
		OccupiedSlot = nullptr;

		//TODO if needed, make an invisible background widget to handle anything dropped outside the menu
	}
	
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;
	GridMenu->SelectedBlock = CreateWidget(GetWorld(), SpellBlueprint);
}

void USpellBlock::UpdateNeighbours()
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
					SetParameters(Cast<UParameterBlock>(CurrentNode), Neighbour);
					
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
					SetParameters(Cast<UParameterBlock>(CurrentNode), Neighbour);
					
				}
			}
			
			
			SetParameters(Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour)), Neighbour);

			
		}

		
	}

	if(OccupiedSlot->Down >= 0 && OccupiedSlot->Down < GridMenu->Slots.Num())
	{
		UParameterBlock* TargetBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(OccupiedSlot->Down));
		SetParameters(Cast<UParameterBlock>(*GridMenu->Slots.Find(OccupiedSlot->Down)), OccupiedSlot->Down);
	}

	if(Target == nullptr)
	{
		//Change to Error material
	}
	
}
