// Fill out your copyright notice in the Description page of Project Settings.


#include "ParameterBlock.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/DragWidget.h"

UDragWidget* UParameterBlock::DragOperator(UDragWidget* DragOperation)
{
	if(OccupiedSlot != nullptr)
	{
		GridMenu->SetSlotInArray(OccupiedSlot, OccupiedSlot->SlotID, true);
		OccupiedSlot->UniGrid->RemoveChild(this);
		OccupiedSlot->SlotImage->SetVisibility(ESlateVisibility::Visible);
		OccupiedSlot = nullptr;
	 	
		//TODO if needed, make an invisible background widget to handle anything dropped outside the menu
	}

	if(!PlacedOnGrid)
	{
		
		SpellBlueprintInstance = CreateWidget(this, SpellBlueprint, TEXT("Parameter Motion"));
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