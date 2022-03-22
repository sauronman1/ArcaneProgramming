#pragma once

#include "Coreminimal.h"
#include "Components/ActorComponent.h"
#include "SpellMotionComponent.generated.h"

UCLASS(BlueprintType, Meta=(BlueprintSpawnableComponent))
class USpellMotionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	
	

	void AddMotion(FVector Direction);
};
