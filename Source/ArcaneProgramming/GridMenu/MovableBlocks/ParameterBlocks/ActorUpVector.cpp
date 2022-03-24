// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUpVector.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/DragWidget.h"

UActorUpVector::UActorUpVector()
{
	ParaType = ParameterType::VectorEnum;
	VType = VectorType::ActorUpVector;
}

FReply UActorUpVector::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;

	return Reply.NativeReply;

}

void UActorUpVector::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragWidget* DragOperation = NewObject<UDragWidget>();
	
	OutOperation = DragOperator(DragOperation);
}

bool UActorUpVector::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	return true;
}

VectorType UActorUpVector::VecType()
{
	
	return VType;
}