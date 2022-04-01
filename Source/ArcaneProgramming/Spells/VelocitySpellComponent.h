// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "Components/ActorComponent.h"
#include "VelocitySpellComponent.generated.h"


class AMagePlayer;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCANEPROGRAMMING_API UVelocitySpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVelocitySpellComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActivateVelocity(FVector InDirection, VectorType VType);
	void AddVelocity(float DeltaTime);
	
private:
	UPROPERTY()
	AMagePlayer* Character;
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	FVector Direction;
	float Timer = 0.f;
	float FireDuration = 5.f;
};
