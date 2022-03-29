// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBlock.h" 

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/DragWidget.h"
#include "Kismet/GameplayStatics.h"

UDragWidget* USpellBlock::DragOperator(UDragWidget* DragOperation)
{
	if(OccupiedSlot != nullptr)
	{
		GridMenu->SetSlotInArray(OccupiedSlot, OccupiedSlot->SlotID, true);
		OccupiedSlot->UniGrid->RemoveChild(this);
		OccupiedSlot->SlotImage->SetVisibility(ESlateVisibility::Visible);
		OccupiedSlot = nullptr;

		//TODO if needed, make an invisible background widget to handle anything dropped outside the menu
	}

	//
	// UUserWidget* Block;
	// TArray<UWidget*> Children;
	// if(!Debbuged)
	// {
	// 	Block = Cast<UGridBlock>(*GridMenu->Slots.Find(0));
	// 	Children = Cast<UGridBlock>(Block)->UniGrid->GetAllChildren();
	//
	// }
	// else
	// {
	// 	
	// 	Block = Cast<USpellBlock>(*GridMenu->Slots.Find(0));
	// 	Children = Cast<USpellBlock>(Block)->OccupiedSlot->UniGrid->GetAllChildren();
	//
	// }
	// Debbuged = true;
	//
	// for (UWidget* Child : Children)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *Child->GetName());
	// }
	//
	
	if(!PlacedOnGrid)
	{
		SpellBlueprintInstance = CreateWidget(GetWorld(), SpellBlueprint);
		DragOperation->DefaultDragVisual = SpellBlueprintInstance;
		DragOperation->WidgetReference = SpellBlueprintInstance;
	}
	else
	{
		DragOperation->DefaultDragVisual = this;
		DragOperation->WidgetReference = this;
		PlacedOnGrid = false;
	}
	return DragOperation;
}


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