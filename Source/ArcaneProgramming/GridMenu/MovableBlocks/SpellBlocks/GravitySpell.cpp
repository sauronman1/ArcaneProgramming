#include "GravitySpell.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"
#include "Components/EditableText.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/Spells/GravitySpellComponent.h"
#include "Kismet/GameplayStatics.h"

void UGravitySpell::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomButton){CustomButton->OnClicked.AddDynamic(this, &USpellBlock::ClickAndDrop);}
		if(SpellDurationBox){SpellDurationBox->OnTextCommitted.AddDynamic(this, &UGravitySpell::SetSpellDuration);}
		if(RemoveGravityBox){RemoveGravityBox->OnCheckStateChanged.AddDynamic(this, &UGravitySpell::SetGravity);}
		MenuSet = true;
	}
}

void UGravitySpell::SetParameters(UParameterBlock* ParameterBlock, int Neighbour)
{
	if(ParameterBlock != nullptr)
	{
		if(ParameterBlock->ParaType == ParameterType::Actor)
			Target = ParameterBlock->Target();
		if(ParameterBlock->ParaType == ParameterType::Primary && Neighbour == OccupiedSlot->Down)
			IsPrimary = true;
		if(ParameterBlock->ParaType == ParameterType::Converter && Neighbour != OccupiedSlot->Right)
			Target = ParameterBlock->Target();
	}
}

void UGravitySpell::ActivateSpell()
{
	Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu->UpdateNeigboursOnAllNodes();
	
	if(Target == nullptr)
	{
		return;
	}

	UGravitySpellComponent* GravitySpell = Target->FindComponentByClass<UGravitySpellComponent>();
	if(GravitySpell == nullptr)
	{
		GravitySpell = NewObject<UGravitySpellComponent>(Target, UGravitySpellComponent::StaticClass());
		GravitySpell->RegisterComponent();
	}
	else
	{
		GravitySpell->SetComponentTickEnabled(true);	
	}
	
	GravitySpell->RemoveTargetGravity(SpellDuration, RemoveGravity);
}

void UGravitySpell::SetSpellDuration(const FText& Text, ETextCommit::Type type)
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

void UGravitySpell::SetGravity(bool CheckedState)
{
	RemoveGravity = CheckedState;
}
