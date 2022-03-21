#include "SpellMotionComponent.h"

#include "Components/CapsuleComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "ArcaneProgramming/Player/MagePlayer.h"
#include "Kismet/GameplayStatics.h"

void USpellMotionComponent::BeginPlay()
{
	AddMotion();
}


void USpellMotionComponent::AddMotion()
{
	Super::BeginPlay();
	
	Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMagePlayer* Character = Cast<AMagePlayer>(Target);
	if(Character != nullptr)
	{
		Character->GetCharacterMovement()->AddImpulse(FMath::Square(200) * FVector::UpVector);
	}
}