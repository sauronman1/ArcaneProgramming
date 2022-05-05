// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravitySpellComponent.generated.h"


class AMagePlayer;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCANEPROGRAMMING_API UGravitySpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGravitySpellComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RemoveTargetGravity(float Duration, bool EnableGravity);
	void ReturnTargetGravity();
private:
	UPROPERTY()
	AMagePlayer* Character;
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	bool LastGravityState = false;
	float LastGravityScale = 0;
	float Timer = 0;
	float SpellDuration = 0;
	
};
