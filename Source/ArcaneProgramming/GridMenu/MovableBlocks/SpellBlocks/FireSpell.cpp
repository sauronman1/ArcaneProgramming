// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSpell.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/PipeBlock.h"
#include "ArcaneProgramming/Spells/FireSpellComponent.h"
#include "Particles/ParticleSystemComponent.h"

void UFireSpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		if(SpellDurationBox){SpellDurationBox->OnTextCommitted.AddDynamic(this, &UFireSpell::SetSpellDuration);}

		MenuSet = true;
	}
}



void UFireSpell::SetParameters(UParameterBlock* ParameterBlock, int Neighbour)
{
	if(ParameterBlock != nullptr)
	{
		if(ParameterBlock->ParaType == ParameterType::Actor)
		{
			Target = ParameterBlock->Target();
		}
		if(ParameterBlock->ParaType == ParameterType::Primary && Neighbour == OccupiedSlot->Down)
			IsPrimary = true;
	}
}


void UFireSpell::ActivateSpell()
{
	UpdateNeighbours();
	
	if(Target == nullptr)
	{
		return;
	}

	UFireSpellComponent* FireSpellComponent = Target->FindComponentByClass<UFireSpellComponent>();
	if(FireSpellComponent == nullptr)
	{
		FireSpellComponent = NewObject<UFireSpellComponent>(Target, UFireSpellComponent::StaticClass());
		FireSpellComponent->RegisterComponent();
		FireSpellComponent->PSComponent = CustomButton->PSComponent;
	}
	else
	{
		FireSpellComponent->SetComponentTickEnabled(true);	
	}

	FireSpellComponent->IncinerateTarget(SpellDuration);
}

void UFireSpell::SetSpellDuration(const FText& Text, ETextCommit::Type type)
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
