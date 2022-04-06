// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocitySpellComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

// Sets default values for this component's properties
UVelocitySpellComponent::UVelocitySpellComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVelocitySpellComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVelocitySpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if(Timer < SpellDuration)
	{
		AddVelocity(DeltaTime);
	}
	else
	{
		
	}
}

void UVelocitySpellComponent::ActivateVelocity(FVector InDirection, const float Duration, float Amplifier,  VectorType VType)
{
	Character = Cast<AMagePlayer>(GetOwner());
	MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	SpellDuration = Duration;
	Direction = InDirection;
	SpeedAmplifier = Amplifier;
	Timer = 0;
	
	if(MeshComponent != nullptr)
	{
		if(VType == VectorType::ActorUpVector)
		{
			Direction = MeshComponent->GetUpVector();
		}
		if(VType == VectorType::ActorForwardVector)
		{
			Direction = MeshComponent->GetForwardVector();
		}
		if(VType == VectorType::ActorRightVector)
		{
			Direction = MeshComponent->GetRightVector();
		}
	}

	if(Character != nullptr)
	{
		if(VType == VectorType::ActorUpVector)
		{
			Direction = Character->Cam->GetUpVector();
		}
		if(VType == VectorType::ActorForwardVector)
		{
			Direction = Character->Cam->GetForwardVector();
		}
		if(VType == VectorType::ActorRightVector)
		{
			Direction = Character->Cam->GetRightVector();
		}
	}
}

void UVelocitySpellComponent::AddVelocity(float DeltaTime)
{
	if(Character != nullptr)
	{
		Character->AddMovementInput(Direction);
	}
	else if(MeshComponent && GetOwner()->IsRootComponentMovable())
	{
		MeshComponent->GetOwner()->AddActorWorldOffset(Direction * DeltaTime * SpeedAmplifier);
	}
}

