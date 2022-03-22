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

	
}