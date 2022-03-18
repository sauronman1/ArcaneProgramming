#include "GridMenu.h"

#include <ThirdParty/PhysX3/PxShared/src/foundation/include/PsArray.h>

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

	int width = 6;
	int height = 6;

	for(int i = 0; i<Array.Num(); i++)
	{
		UGridBlock* block = Cast<UGridBlock>(Array[i]);
		Slots.Add(block->SlotID, Array[i]);
	}

	int currentIndex = 0;
	for (int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			UGridBlock* block = Cast<UGridBlock>(*Slots.Find(currentIndex));

			if(y == 0 && x == 0)
			{
				block->Left = -1;
				block->Up = -1;
				block->Right = currentIndex + 1;
				block->Down = currentIndex + 6;
			}
			else if(y == 0 && x == width)
			{
				block->Left = currentIndex - 1;
				block->Up = -1;
				block->Right = -1;
				block->Down = currentIndex + 6;
			}
			else if(y == height && x == 0)
			{
				block->Left = -1;
				block->Up = currentIndex - 6;
				block->Right = currentIndex + 1;
				block->Down = -1;
			}
			else if(y == height && x == width)
			{
				block->Left = currentIndex - 1;
				block->Up = currentIndex - 6;
				block->Right = -1;
				block->Down = -1;
			}
			else if(y == 0)
			{
				block->Left = currentIndex - 1;
				block->Up = -1;
				block->Right = currentIndex + 1;
				block->Down = currentIndex + 6;
			}
			else if(y == height)
			{
				block->Left = currentIndex - 1;
				block->Up = currentIndex-6;
				block->Right = currentIndex + 1;
				block->Down = -1;
			}
			else if(x == 0)
			{
				block->Left = -1;
				block->Up = currentIndex - 6;
				block->Right = currentIndex + 1;
				block->Down = currentIndex + 6;
			}
			else if(x == width)
			{
				block->Left = currentIndex - 1;
				block->Up = currentIndex - 6;
				block->Right = -1;
				block->Down = currentIndex + 6;
			}
			else
			{
				block->Left = currentIndex - 1;
				block->Up = currentIndex - 6;
				block->Right = currentIndex + 1;
				block->Down = currentIndex + 6;
			}

			currentIndex++;
		}
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

