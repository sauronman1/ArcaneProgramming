// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTarget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

UPlayerTarget::UPlayerTarget()
{
	ParaType = ParameterType::Actor;
}

void UPlayerTarget::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		MenuSet = true;
	}
}

AActor* UPlayerTarget::Target()
{
	
	AActor* Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//AMagePlayer* Character = Cast<AMagePlayer>(Target);
	return Target;
}
