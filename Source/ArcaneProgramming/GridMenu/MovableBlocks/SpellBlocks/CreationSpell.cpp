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
				if(TargetBlock->ParaType == ParameterType::Actor)
				{
					Target = TargetBlock->Target();
				}
				if(TargetBlock->ParaType == ParameterType::VectorEnum)
				{
					DirectionToSpawnRelativeToSpawner = TargetBlock->VType; 
				}
			}

			
		}

		
	}

	if(OccupiedSlot->Down >= 0 && OccupiedSlot->Down < GridMenu->Slots.Num())
	{
		UParameterBlock* TargetBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(OccupiedSlot->Down));
		if(TargetBlock != nullptr)
		{
			if(TargetBlock->ParaType == ParameterType::Primary)
				IsPrimary = true;
		}

			
	}
	
}

void UCreationSpell::ActivateSpell()
{
	UpdateNeighbours();
	AStaticMeshActor* NewMesh = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(0, 0, 0), FRotator(0, 0, 0));
	NewMesh->SetMobility(EComponentMobility::Movable);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetStaticMesh(CustomButton->Target->GetStaticMesh());
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetEnableGravity(false);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetLinearDamping(1.f);
	SpellTarget = NewMesh;
	
	UCreationSpellComponent* CreationSpellComponent = NewMesh->FindComponentByClass<UCreationSpellComponent>();
	if(CreationSpellComponent == nullptr)
	{
		CreationSpellComponent = NewObject<UCreationSpellComponent>(NewMesh, UCreationSpellComponent::StaticClass());
		CreationSpellComponent->RegisterComponent();
	}

	TArray<int> Neighbours = {OccupiedSlot->Right, OccupiedSlot->Up, OccupiedSlot->Left, OccupiedSlot->Down};

	for (int Neighbour : Neighbours)
	{
		if(Neighbour >= 0 && Neighbour < GridMenu->Slots.Num())
		{
			UParameterBlock* TargetBlock = Cast<UParameterBlock>(*GridMenu->Slots.Find(Neighbour));
			if(TargetBlock != nullptr)
			{
				TargetBlock->UpdateNeighbours();
			}
		}
	}
	
	CreationSpellComponent->SetPosition(Target, DirectionToSpawnRelativeToSpawner);
	
}