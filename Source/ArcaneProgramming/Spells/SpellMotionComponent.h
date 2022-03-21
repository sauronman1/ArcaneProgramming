#pragma once

#include "Coreminimal.h"
#include "Components/ActorComponent.h"
#include "SpellMotionComponent.generated.h"

UCLASS()
class USpellMotionComponent : public UActorComponent
{
	GENERATED_BODY()

	AActor* Target;
	FVector Direction;

	
};
