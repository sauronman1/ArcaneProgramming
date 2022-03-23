// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtTarget.h"

#include "DrawDebugHelpers.h"
#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/DragWidget.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

ULookAtTarget::ULookAtTarget()
{
	ParaType = ParameterType::Actor;
}

FReply ULookAtTarget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;

	return Reply.NativeReply;

}

void ULookAtTarget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UDragWidget* DragOperation = NewObject<UDragWidget>();
	
	OutOperation = DragOperator(DragOperation);
}

bool ULookAtTarget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	return true;
}


AActor* ULookAtTarget::Target()
{
	AActor* Target = nullptr;

	FHitResult HitResult;

	const FVector Start = Cast<AMagePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Cam->GetComponentLocation();
	FVector End = Start + Cast<AMagePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Cam->GetComponentRotation().Vector() * TraceDistance;

	FCollisionQueryParams TraceParams;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);

	if(IsHit)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.1f);
		Target = HitResult.GetActor();
	}
	
	//AMagePlayer* Character = Cast<AMagePlayer>(Target);
	return Target;
}