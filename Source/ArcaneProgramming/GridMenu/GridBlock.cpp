#include "GridBlock.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "MovableBlocks/SpellBlocks/SpellBlock.h"

void UGridBlock::NativeConstruct()
{

	if(!MenuSet)
	{
		if(CustomGridButton){CustomGridButton->OnClicked.AddDynamic(this, &UGridBlock::ClickAndDrop);}
		MenuSet = true;
	}
}

void UGridBlock::ClickAndDrop()
{
	UGridMenu* GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;
	if(GridMenu->SelectedBlock == nullptr)
	{
		return;
	}
	
	GridMenu->SelectedBlock->AddToViewport();
	SlotImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	UniGrid->AddChildToUniformGrid(GridMenu->SelectedBlock);

	USpellBlock* SpellBlock = Cast<USpellBlock>(GridMenu->SelectedBlock);
	if(SpellBlock != nullptr)
	{
		SpellBlock->PlacedOnGrid = true;
		SpellBlock->OccupiedSlot = this;
		SpellBlock->SlotID = SlotID;
		SpellBlock->GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;
	}

	UParameterBlock* ParameterBlock = Cast<UParameterBlock>(GridMenu->SelectedBlock);
	if(ParameterBlock != nullptr)
	{
		ParameterBlock->PlacedOnGrid = true;
		ParameterBlock->OccupiedSlot = this;
		ParameterBlock->SlotID = SlotID;
		ParameterBlock->GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;

	}

	AArcaneGameModeBase* GameMode = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GridMenu->SetSlotInArray(GridMenu->SelectedBlock, SlotID, false);
	GridMenu->SelectedBlock = nullptr;
}
