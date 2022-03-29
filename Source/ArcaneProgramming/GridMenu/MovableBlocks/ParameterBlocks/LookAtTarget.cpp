// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtTarget.h"

#include "DrawDebugHelpers.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/GridMenu/GridBlock.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

ULookAtTarget::ULookAtTarget()
{
	ParaType = ParameterType::Actor;
}

void ULookAtTarget::NativeConstruct()
{
	if(!MenuSet)
	{
		if(CustomParameterButton){CustomParameterButton->OnClicked.AddDynamic(this, &UParameterBlock::ClickAndDrop);}
		MenuSet = true;
	}
}

AActor* ULookAtTarget::Target()
{
	AActor* Target = nullptr;

	FHitResult HitResult;

	const FVector Start = Cast<AMagePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Cam->GetComponentLocation();
	FVector End = Start + Cast<AMagePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Cam->GetComponentRotation().Vector() * TraceDistance;

	FCollisionQueryParams TraceParams;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);

	if(IsHit)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.1f);
		Target = HitResult.GetActor();
	}
	
	//AMagePlayer* Character = Cast<AMagePlayer>(Target);
	return Target;
}