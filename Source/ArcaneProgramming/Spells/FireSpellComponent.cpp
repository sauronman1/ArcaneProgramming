// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSpellComponent.h"

#include "ArcaneProgramming/Player/MagePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values for this component's properties
UFireSpellComponent::UFireSpellComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireSpellComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFireSpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if(Timer > FireDuration)
	{
		Particlesystem->DeactivateSystem();
		Deactivate();
	}
}

void UFireSpellComponent::IncinerateTarget()
{
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if(Character != nullptr)
	{
		
			Timer = 0;

			Particlesystem = UGameplayStatics::SpawnEmitterAttached(PSComponent->Template, Character->GetRootComponent(),NAME_None,   Character->GetActorLocation());
			Particlesystem->SetRelativeLocation(FVector(0,0,0));
		
		
	}
	if(MeshComponent != nullptr)
	{
		
			Timer = 0;
			Particlesystem = UGameplayStatics::SpawnEmitterAttached(PSComponent->Template, MeshComponent,NAME_None, MeshComponent->GetComponentLocation());
			Particlesystem->SetRelativeLocation(FVector(0,0,0));
		//TODO Reactivate partticles instead of creating a new one each time
		

	}
}


