#include "GridMenu.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GridBlock.h"
#include "MovableBlocks/SpellBlock.h"

void UGridMenu::NativeConstruct()
{
	AArcaneGameModeBase* GameModeBase = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameModeBase->GridMenu = this;
	SetEmptySlots();
	//TODO Spell and Parameter block will inherit base class so when iterating through array, will only care about the ones that inherit from it
	//TODO When adding nes spells/parameter blocks to the grid, check if their neighbours are not empty to know if they should add them as parameters
	//TODO Make a primary block or slot on menu to help set a spell as primary spell
	//TODO Set the IDs on the gridmenu again
}


void UGridMenu::SetEmptySlots()
{
	TArray<UWidget*> Array = GridBlockPanel->GetAllChildren();
	Slots.SetNum(Array.Num());
	for (int i = 0; i < Array.Num(); i++)
	{
		Slots[i] = Cast<UUserWidget>(Array[i]);
	}
}

void UGridMenu::SetSlotInArray(UUserWidget* Block, int SlotID)
{	
	Slots[SlotID] = Block;
	for(int i = 0; i<Slots.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %d"), *Slots[i]->GetName(), i);
	}
}

