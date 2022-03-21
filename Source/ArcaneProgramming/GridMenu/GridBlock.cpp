#include "GridBlock.h"

#include "DragWidget.h"
#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "MovableBlocks/SpellBlocks/SpellBlock.h"

void UGridBlock::NativeConstruct()
{
	//gridPanel = Cast<UGridPanel>(GetParent());
	//if(ButtonObj){ButtonObj->OnClicked.AddDynamic(this, &UGridBlock::GetPanel);}

	//UWidgetBlueprintLibrary::det
}

void UGridBlock::GetPanel()
{
	UE_LOG(LogTemp, Warning, TEXT("gjgs"));
}

bool UGridBlock::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UDragWidget* InDragAndDrop = Cast<UDragWidget>(InOperation);
	InDragAndDrop->WidgetReference->AddToViewport();
	SlotImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	UniGrid->AddChildToUniformGrid(InDragAndDrop->WidgetReference);
	Cast<USpellBlock>(InDragAndDrop->WidgetReference)->PlacedOnGrid = true;
	Cast<USpellBlock>(InDragAndDrop->WidgetReference)->OccupiedSlot = this;
	Cast<USpellBlock>(InDragAndDrop->WidgetReference)->SlotID = SlotID;

	AArcaneGameModeBase* GameMode = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GridMenu->SetSlotInArray(InDragAndDrop->WidgetReference, SlotID, false);
	
	return true;
}