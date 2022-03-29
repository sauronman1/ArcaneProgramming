// Fill out your copyright notice in the Description page of Project Settings.


#include "CreationSpell.h"

#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/Spells/CreationSpellComponent.h"
#include "Engine/StaticMeshActor.h"

void UCreationSpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		MenuSet = true;
	}
}



void UCreationSpell::UpdateNeighbours()
{
	TArray<int> Neighbours = {OccupiedSlot->Right, OccupiedSlot->Up, OccupiedSlot->Left, OccupiedSlot->Down};

	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UParameterBlock* TargetBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
			if(TargetBlock != nullptr)
			{
				if(TargetBlock->ParaType == ParameterType::Position)
				{
					Position = TargetBlock->Position();
				}
			}

			
		}

		
	}
	
}

void UCreationSpell::ActivateSpell()
{
	UpdateNeighbours();
	AStaticMeshActor* NewMesh = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(0, 0, 0), FRotator(0, 0, 0));
	NewMesh->SetMobility(EComponentMobility::Movable);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetStaticMesh(CustomButton->Target->GetStaticMesh());

	// UCreationSpellComponent* CreationSpellComponent = NewMesh->FindComponentByClass<UCreationSpellComponent>();
	// if(CreationSpellComponent == nullptr)
	// {
	// 	CreationSpellComponent = NewObject<UCreationSpellComponent>(Target, UCreationSpell::StaticClass());
	// 	CreationSpellComponent->RegisterComponent();
	// }
	//
	
	
}