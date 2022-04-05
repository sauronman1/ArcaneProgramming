#pragma once

#include "Coreminimal.h"

#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "Components/ActorComponent.h"
#include "MotionSpellComponent.generated.h"

UCLASS(BlueprintType, Meta=(BlueprintSpawnableComponent))
class UMotionSpellComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	
	

	void AddMotion(FVector Direction, float Amplifier, VectorType VType);
};
