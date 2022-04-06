// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocitySpell.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/Spells/VelocitySpellComponent.h"


void UVelocitySpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		if(SpellDurationBox){SpellDurationBox->OnTextCommitted.AddDynamic(this, &UVelocitySpell::SetSpellDuration);}

		MenuSet = true;
	}
}



void UVelocitySpell::UpdateNeighbours()
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
				if(TargetBlock->ParaType == ParameterType::Direction)
				{
					Direction = TargetBlock->Direction();
				}
				if(TargetBlock->ParaType == ParameterType::VectorEnum)
				{
					VType = TargetBlock->VType;
					Amplifier = TargetBlock->Amplifier;
				}
			}

			
		}

		
	}

	if(Target == nullptr)
	{
		//Change to Error material
	}
	
}

void UVelocitySpell::ActivateSpell()
{
	UpdateNeighbours();
	
	if(Target == nullptr)
	{
		return;
	}

	UVelocitySpellComponent* VelocitySpellComponent = Target->FindComponentByClass<UVelocitySpellComponent>();
	if(VelocitySpellComponent == nullptr)
	{
		VelocitySpellComponent = NewObject<UVelocitySpellComponent>(Target, UVelocitySpellComponent::StaticClass());
		VelocitySpellComponent->RegisterComponent();
	}

	
	
	VelocitySpellComponent->ActivateVelocity(Direction, SpellDuration, Amplifier, VType);
}

void UVelocitySpell::SetSpellDuration(const FText& Text, ETextCommit::Type type)
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