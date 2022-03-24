#pragma once

#include "Coreminimal.h"

#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "Components/ActorComponent.h"
#include "SpellMotionComponent.generated.h"

UCLASS(BlueprintType, Meta=(BlueprintSpawnableComponent))
class USpellMotionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	
	

	void AddMotion(FVector Direction, VectorType VType);
};
