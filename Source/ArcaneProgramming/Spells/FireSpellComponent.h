// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"

#include "FireSpellComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCANEPROGRAMMING_API UFireSpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireSpellComponent();

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* PSComponent;
	UPROPERTY()
	TArray<AActor*> IgnoreActors;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void IncinerateTarget(float Duration);
	

private:
	float Timer = 0.f;
	float DamageTimer = 0.f;
	float FireDuration = 0.f;

	UPROPERTY()
	USphereComponent* SphereComponent;
	UPROPERTY()
	UParticleSystemComponent* Particlesystem;

	UFUNCTION()
	void HandleCollision();
};
