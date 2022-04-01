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
	if(Timer < FireDuration)
	{
		AddVelocity(DeltaTime);
	}
}

void UVelocitySpellComponent::ActivateVelocity(FVector InDirection, VectorType VType)
{
	Character = Cast<AMagePlayer>(GetOwner());
	MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	Direction = InDirection;
	
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
		
	
	if(Character != nullptr)
	{
		//Character->GetCharacterMovement()->
	}
	else if(MeshComponent && GetOwner()->IsRootComponentMovable())
	{
		Timer = 0;
		MeshComponent->AddForce(Direction * 100.f * MeshComponent->GetMass());
		//MeshComponent->AddImpulse(Direction * 500.f * MeshComponent->GetMass());
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
		Timer = 0;
		MeshComponent->GetOwner()->AddActorWorldOffset(Direction * DeltaTime * 100.f);
		
	}
}

