// Fill out your copyright notice in the Description page of Project Settings.


#include "CreationSpellComponent.h"

#include "ArcaneProgramming/GridMenu/MovableBlocks/ParameterBlocks/ParameterBlock.h"
#include "ArcaneProgramming/Player/MagePlayer.h"
#include "Engine/StaticMeshActor.h"

UCreationSpellComponent::UCreationSpellComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCreationSpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if(Timer > SpellDuration)
	{
		GetOwner()->Destroy();
	}
}

void UCreationSpellComponent::SetPosition(AActor* TargetSpawner, float Duration, float DistanceFromCreationOrigin, VectorType DirectionToSpawnRelativeToSpawner)
{
	AMagePlayer* Character = Cast<AMagePlayer>(TargetSpawner);
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(TargetSpawner->GetRootComponent());

	FVector SpawnPosition;
	FRotator SpawnRotation;
	SpellDuration = Duration;
	
	if(MeshComponent != nullptr)
	{
		
		if(DirectionToSpawnRelativeToSpawner == VectorType::ActorUpVector)
		{
			SpawnPosition = MeshComponent->GetComponentLocation();
			SpawnPosition += MeshComponent->GetUpVector() * DistanceFromCreationOrigin;
			GetOwner()->SetActorLocation(SpawnPosition);
		}
		if(DirectionToSpawnRelativeToSpawner == VectorType::ActorForwardVector)
		{
			SpawnPosition = MeshComponent->GetComponentLocation();
			SpawnPosition += MeshComponent->GetForwardVector() * DistanceFromCreationOrigin;
			GetOwner()->SetActorLocation(SpawnPosition);
		}
		if(DirectionToSpawnRelativeToSpawner == VectorType::ActorRightVector)
		{
			SpawnPosition = MeshComponent->GetComponentLocation();
			SpawnPosition += MeshComponent->GetRightVector() * DistanceFromCreationOrigin;
			GetOwner()->SetActorLocation(SpawnPosition);
		}
		SpawnRotation = MeshComponent->GetComponentRotation();
		GetOwner()->SetActorRotation(SpawnRotation);
	}

	if(Character != nullptr)
	{
		if(DirectionToSpawnRelativeToSpawner == VectorType::ActorUpVector)
		{
			SpawnPosition = Character->Cam->GetComponentLocation();
			SpawnPosition += Character->Cam->GetUpVector() * DistanceFromCreationOrigin;
			GetOwner()->SetActorLocation(SpawnPosition);
		}
		if(DirectionToSpawnRelativeToSpawner == VectorType::ActorForwardVector)
		{
			SpawnPosition = Character->Cam->GetComponentLocation();
			SpawnPosition += Character->Cam->GetForwardVector() * DistanceFromCreationOrigin;
			GetOwner()->SetActorLocation(SpawnPosition);
		}
		if(DirectionToSpawnRelativeToSpawner == VectorType::ActorRightVector)
		{
			SpawnPosition = Character->Cam->GetComponentLocation();
			SpawnPosition += Character->Cam->GetRightVector() * DistanceFromCreationOrigin;
			GetOwner()->SetActorLocation(SpawnPosition);
			
		}
		
		SpawnRotation = Character->Cam->GetComponentRotation();
		GetOwner()->SetActorRotation(SpawnRotation);
	}
}

