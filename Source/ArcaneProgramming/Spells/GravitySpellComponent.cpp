#include "GravitySpellComponent.h"
#include "ArcaneProgramming/Player/MagePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values for this component's properties
UGravitySpellComponent::UGravitySpellComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGravitySpellComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGravitySpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if(Timer > SpellDuration)
	{
		ReturnTargetGravity();
		SetComponentTickEnabled(false);
	}
}

void UGravitySpellComponent::RemoveTargetGravity(float Duration, bool RemoveGravity)
{
	Character = Cast<AMagePlayer>(GetOwner());
	MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	SpellDuration = Duration;
	Timer = 0;
	
	if(MeshComponent != nullptr)
	{
		LastGravityState = MeshComponent->IsGravityEnabled();

		if(RemoveGravity)
			MeshComponent->SetEnableGravity(false);
		else
			MeshComponent->SetEnableGravity(true);			
	}
	if(Character != nullptr)
	{
		LastGravityScale = Character->GetCharacterMovement()->GravityScale;

		if(RemoveGravity)
			Character->GetCharacterMovement()->GravityScale = 0;
		else
			Character->GetCharacterMovement()->GravityScale = 1;			
	}
}

void UGravitySpellComponent::ReturnTargetGravity() 
{
	if(MeshComponent != nullptr)
	{
		MeshComponent->SetEnableGravity(LastGravityState);
	}
	if(Character != nullptr)
	{
		Character->GetCharacterMovement()->GravityScale = LastGravityScale;
	}
}
