// Fill out your copyright notice in the Description page of Project Settings.


#include "MotionSpell.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/DragWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "Kismet/GameplayStatics.h"

FReply UMotionSpell::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;
	return Reply.NativeReply;

}

void UMotionSpell::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragWidget* DragOperation = NewObject<UDragWidget>();
	 if(OccupiedSlot != nullptr)
	 {
	 	GridMenu->SetSlotInArray(OccupiedSlot, OccupiedSlot->SlotID);
	 	OccupiedSlot->UniGrid->RemoveChild(this);
	 }

	if(!PlacedOnGrid)
	{
		
		SpellBlueprintInstance = CreateWidget(this, SpellBlueprint, TEXT("Spell Motion"));
		DragOperation->DefaultDragVisual = SpellBlueprintInstance;
		DragOperation->WidgetReference = SpellBlueprintInstance;
	}
	else
	{
		DragOperation->DefaultDragVisual = this;
		DragOperation->WidgetReference = this;
	}
	
	OutOperation = DragOperation;
}

bool UMotionSpell::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	return true;
}

void UMotionSpell::UpdateNeighbours()
{
	
}



