#include "SpellMotionComponent.h"

#include "Gameframework/CharacterMovementComponent.h"
#include "ArcaneProgramming/Player/MagePlayer.h"

void USpellMotionComponent::AddMotion(FVector Direction)
{
	
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	if(Character != nullptr)
	{
		Character->GetCharacterMovement()->AddImpulse(FMath::Square(200) * FVector::UpVector);
	}

	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if(MeshComponent && GetOwner()->IsRootComponentMovable())
	{
		FVector Up = FVector::UpVector;
		MeshComponent->AddImpulse(Up * 500.f * MeshComponent->GetMass());
	}

	
}