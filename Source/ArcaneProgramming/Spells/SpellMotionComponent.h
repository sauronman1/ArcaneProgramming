#pragma once

#include "Coreminimal.h"
#include "Components/ActorComponent.h"
#include "SpellMotionComponent.generated.h"

UCLASS(BlueprintType, Meta=(BlueprintSpawnableComponent))
class USpellMotionComponent : public UActorComponent
{
	GENERATED_BODY()

	AActor* Target;
	FVector Direction;

	virtual void BeginPlay() override;
	void AddMotion();
};
