#include "MotionSpellComponent.h"

#include "Gameframework/CharacterMovementComponent.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

void UMotionSpellComponent::AddMotion(FVector Direction, float Amplifier, VectorType VType)
{
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

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
			Direction = Character->GetActorUpVector();
		}
		if(VType == VectorType::ActorForwardVector)
		{
			Direction = Character->GetActorForwardVector();
		}
		if(VType == VectorType::ActorRightVector)
		{
			Direction = Character->GetActorRightVector();
		}
	}
		
	
	if(Character != nullptr)
	{
	 	Character->GetCharacterMovement()->AddImpulse(FMath::Square(Amplifier) * Direction);
	}

	if(MeshComponent && GetOwner()->IsRootComponentMovable())
	{

		MeshComponent->AddImpulse(Direction * Amplifier * MeshComponent->GetMass());
	}

	
}