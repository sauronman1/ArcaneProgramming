#include "GridMenu.h"
#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GridBlock.h"
#include "MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "MovableBlocks/ParameterBlocks/PipeBlock.h"
#include "MovableBlocks/SpellBlocks/SpellBlock.h"

void UGridMenu::NativeConstruct()
{
	AArcaneGameModeBase* GameModeBase = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameModeBase->GridMenu = this;
	if(!MenuSet)
	{
		if(ChannelButton){ChannelButton->OnClicked.AddDynamic(this, &UGridMenu::UpdateNeigboursOnAllNodes);}
		SetEmptySlots();
		ShowManaCost();
		MenuSet = true;
	}
	
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

void UGridMenu::SetSlotInArray(UUserWidget* InBlock, int SlotID, bool RemoveBlock)
{	
	
	if(!RemoveBlock)
	{
		UGridBlock* CurrentBlock = Cast<UGridBlock>(*Slots.Find(SlotID));
		if(CurrentBlock != nullptr)
		{
			USpellBlock* SpellBlock = Cast<USpellBlock>(InBlock);
			if(SpellBlock != nullptr)
			{
				Slots.Add(SlotID, SpellBlock);
				SpellBlock->UpdateNeighbours();
			}
			
			UParameterBlock* ParameterBlock = Cast<UParameterBlock>(InBlock);
			if(ParameterBlock != nullptr)
			{
				Slots.Add(SlotID, ParameterBlock);
				ParameterBlock->UpdateNeighbours();
			}
		}
	}
	else
	{			
		USpellBlock* SpellBlock = Cast<USpellBlock>(*Slots.Find(SlotID));
		UParameterBlock* ParameterBlock = Cast<UParameterBlock>(*Slots.Find(SlotID));
		if(SpellBlock != nullptr || ParameterBlock != nullptr)
		{
			UGridBlock* GridBlock = Cast<UGridBlock>(InBlock);
			Slots.Add(SlotID, GridBlock);
		}
		
	}

	for(int i = 0; i<Slots.Num(); i++)
		UE_LOG(LogTemp, Warning, TEXT("%s %d"), *Slots[i]->GetName(), i);
}

void UGridMenu::UpdateNeigboursOnAllNodes()
{
	NullifyAllPipes();
	
	for(int i = 0; i<Slots.Num(); i++)
	{
		USpellBlock* SpellBlock = Cast<USpellBlock>(Slots[i]);
		if(SpellBlock != nullptr)
		{
			SpellBlock->Target = nullptr;
			SpellBlock->Amplifier = 0;
			SpellBlock->IsPrimary = false;
			SpellBlock->TargetFound = false;
		}
	}
	for(int i = 0; i<Slots.Num(); i++)
	{
		UParameterBlock* ParameterBlock = Cast<UParameterBlock>(Slots[i]);
		UPipeBlock* PipeBlock = Cast<UPipeBlock>(Slots[i]);
		if(ParameterBlock != nullptr && PipeBlock == nullptr)
			ParameterBlock->UpdateNeighbours();

		USpellBlock* SpellBlock = Cast<USpellBlock>(Slots[i]);
		if(SpellBlock != nullptr)
			SpellBlock->UpdateNeighbours();
	}

	ShowManaCost();
}

void UGridMenu::ShowManaCost()
{
	ManaCost = 0;
	
	for(int i = 0; i<Slots.Num(); i++)
	{
		USpellBlock* SpellBlock = Cast<USpellBlock>(Slots[i]);
		if(SpellBlock != nullptr)
		{
			ManaCost++;
			ManaCost += FMath::RoundToInt(SpellBlock->SpellDuration/DurationToCostConversion);
		}

		UParameterBlock* ParameterBlock = Cast<UParameterBlock>(Slots[i]);
		if(ParameterBlock != nullptr)
		{
			ManaCost += FMath::RoundToInt(ParameterBlock->Amplifier/AmplifierToCostConversion);
		}
	}

	ManaPoolDisplay->SetText(FText::AsNumber(ManaPool));
	ManaCostDisplay->SetText(FText::AsNumber(ManaCost));

	if(ManaCost > ManaPool)
		ManaCostDisplay->SetColorAndOpacity(FLinearColor::Red);
	else
		ManaCostDisplay->SetColorAndOpacity(FLinearColor::Green);
		
	
	
}

void UGridMenu::NullifyAllPipes()
{
	for(int i = 0; i<Slots.Num(); i++)
	{
		UPipeBlock* PipeBlock = Cast<UPipeBlock>(Slots[i]);
		if(PipeBlock != nullptr)
		{
			PipeBlock->TailNode = nullptr;
			PipeBlock->HeadNode = nullptr;
			PipeBlock->NextNode = nullptr;
			PipeBlock->PreviousNode = nullptr;
		}

		
	}
}

