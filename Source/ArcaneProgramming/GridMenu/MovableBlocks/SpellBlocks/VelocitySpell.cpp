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



void UVelocitySpell::SetParameters(UParameterBlock* ParameterBlock, int Neighbour)
{
	if(ParameterBlock != nullptr)
	{
		if(ParameterBlock->ParaType == ParameterType::Actor)
		{
			Target = ParameterBlock->Target();
		}
		if(ParameterBlock->ParaType == ParameterType::Direction)
		{
			Direction = ParameterBlock->Direction();
		}
		if(ParameterBlock->ParaType == ParameterType::VectorEnum)
		{
			VType = ParameterBlock->VType;
			Amplifier = ParameterBlock->Amplifier;
		}
		if(ParameterBlock->ParaType == ParameterType::Primary && Neighbour == OccupiedSlot->Down)
			IsPrimary = true;
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