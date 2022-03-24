#include "SpellMotionComponent.h"

#include "Gameframework/CharacterMovementComponent.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

void USpellMotionComponent::AddMotion(FVector Direction, VectorType VType)
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
	 	Character->GetCharacterMovement()->AddImpulse(FMath::Square(200) * Direction);
	}

	if(MeshComponent && GetOwner()->IsRootComponentMovable())
	{

		MeshComponent->AddImpulse(Direction * 500.f * MeshComponent->GetMass());
	}

	
}