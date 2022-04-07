// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSpellComponent.h"

#include "ArcaneProgramming/Player/MagePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values for this component's properties
UFireSpellComponent::UFireSpellComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}



// Called every frame
void UFireSpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer += DeltaTime;
	if(Timer > FireDuration)
	{
		if(!ensure(Particlesystem != nullptr))
		{
			return;
		}
		//TODO Add overlapcomponent and resize it depending on parameterblock size
 		Particlesystem->DeactivateSystem();
		Deactivate();
	}
}

void UFireSpellComponent::IncinerateTarget(float Duration)
{
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FireDuration = Duration;

	// SphereComponent = NewObject<USphereComponent>();
	// GetOwner()->SetRootComponent(SphereComponent);
	//
	// SphereComponent->SetRelativeLocation(FVector(0,0,0));
	// SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UFireSpellComponent::HandleBeginOverlap);
	// SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UFireSpellComponent::HandleEndOverlap);
	
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

void UFireSpellComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter"));
}

void UFireSpellComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Exit"));

}


