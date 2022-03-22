// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTarget.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/DragWidget.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "ArcaneProgramming/Player/MagePlayer.h"
#include "Gameframework/CharacterMovementComponent.h"

UPlayerTarget::UPlayerTarget()
{
	ParaType = ParameterType::Actor;
}


FReply UPlayerTarget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;

	return Reply.NativeReply;

}

void UPlayerTarget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragWidget* DragOperation = NewObject<UDragWidget>();
	
	OutOperation = DragOperator(DragOperation);
}

bool UPlayerTarget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	return true;
}

void UPlayerTarget::UpdateNeighbours()
{
	TArray<int> Neighbours = {OccupiedSlot->Right, OccupiedSlot->Up, OccupiedSlot->Left, OccupiedSlot->Down};

	//TODO IMplement this in parent class with name updateSpellNeighbours and and replace code in this function with updating neighbours if parameter block takes in parameter

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

AActor* UPlayerTarget::Target()
{
	

	AActor* Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//AMagePlayer* Character = Cast<AMagePlayer>(Target);
	return Target;
}
