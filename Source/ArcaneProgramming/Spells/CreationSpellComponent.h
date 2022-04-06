// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "Components/ActorComponent.h"
#include "CreationSpellComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCANEPROGRAMMING_API UCreationSpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCreationSpellComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPosition(AActor* TargetSpawner, float Duration, float DistanceFromCreationOrigin,  VectorType DirectionToSpawnRelativeToSpawner);
	
private:
	float Timer = 0.f;
	float SpellDuration = 3.f;
};
