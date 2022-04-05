// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorDirectionVector.h"

#include <string>

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ArcaneProgramming/GridMenu/CustomButton.h"

UActorDirectionVector::UActorDirectionVector()
{
	ParaType = ParameterType::VectorEnum;
	VType = VectorType::ActorUpVector;
}

void UActorDirectionVector::NativeConstruct()
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), Amplifier);
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		if(AmplifierBox){AmplifierBox->OnTextCommitted.AddDynamic(this, &UActorDirectionVector::SetAmplifier);}
		MenuSet = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), Amplifier);

}

VectorType UActorDirectionVector::VecType()
{
	return VType;
}

void UActorDirectionVector::SetAmplifier(const FText& Text, ETextCommit::Type type)
{
	if(AmplifierBox->GetText().IsNumeric())
	{
		Amplifier = FCString::Atof(*AmplifierBox->GetText().ToString());
		
		const FString InputText = FString::SanitizeFloat(Amplifier);
		const FText FText = FText::FromString(InputText);
		
		AmplifierBox->SetText(FText);
	}
	else
	{
		Amplifier = 0;
	}
}

