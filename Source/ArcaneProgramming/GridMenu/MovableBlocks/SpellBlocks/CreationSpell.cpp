// Fill out your copyright notice in the Description page of Project Settings.


#include "CreationSpell.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"
#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/Spells/CreationSpellComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

void UCreationSpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		if(SpellDurationBox){SpellDurationBox->OnTextCommitted.AddDynamic(this, &UCreationSpell::SetSpellDuration);}
		MenuSet = true;
	}
}



void UCreationSpell::SetParameters(UParameterBlock* ParameterBlock, int Neighbour)
{
	if(ParameterBlock != nullptr)
	{
		if(ParameterBlock->ParaType == ParameterType::Actor)
		{
			Target = ParameterBlock->Target();
		}
		if(ParameterBlock->ParaType == ParameterType::VectorEnum)
		{
			DirectionToSpawnRelativeToSpawner = ParameterBlock->VType;
			Amplifier = ParameterBlock->Amplifier;
		}
		if(ParameterBlock->ParaType == ParameterType::Primary && Neighbour == OccupiedSlot->Down)
			IsPrimary = true;
		if(ParameterBlock->ParaType == ParameterType::Converter && Neighbour != OccupiedSlot->Right)
			Target = ParameterBlock->Target();
	}
}


void UCreationSpell::ActivateSpell()
{
	Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu->UpdateNeigboursOnAllNodes();

	AStaticMeshActor* NewMesh = GetWorld()->SpawnActor<AStaticMeshActor>(FVector(0, 0, 0), FRotator(0, 0, 0));
	NewMesh->SetMobility(EComponentMobility::Movable);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetStaticMesh(CustomButton->Target->GetStaticMesh());
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetLinearDamping(1.f);
	NewMesh->FindComponentByClass<UStaticMeshComponent>()->SetRelativeScale3D(FVector(0.2f, 0.2f,0.2f));
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
	
	CreationSpellComponent->SetPosition(Target, SpellDuration, Amplifier, DirectionToSpawnRelativeToSpawner);
	
}

void UCreationSpell::SetSpellDuration(const FText& Text, ETextCommit::Type type)
{
	if(SpellDurationBox->GetText().IsNumeric())
	{
		SpellDuration = FCString::Atof(*SpellDurationBox->GetText().ToString());
		
		const FString InputText = FString::SanitizeFloat(SpellDuration);
		const FText FText = FText::FromString(InputText);
		
		SpellDurationBox->SetText(FText);
	}
	else
	{
		SpellDuration = 1;
	}
}