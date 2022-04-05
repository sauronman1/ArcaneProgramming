// Fill out your copyright notice in the Description page of Project Settings.


#include "ParameterBlock.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "Kismet/GameplayStatics.h"

void UParameterBlock::UpdateNeighbours()
{
	TArray<int> Neighbours = {OccupiedSlot->Right, OccupiedSlot->Up, OccupiedSlot->Left, OccupiedSlot->Down};

	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
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

		//TODO if needed, make an invisible background widget to handle anything dropped outside the menu
	}
	
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;
	GridMenu->SelectedBlock = CreateWidget(GetWorld(), SpellBlueprint);
}


