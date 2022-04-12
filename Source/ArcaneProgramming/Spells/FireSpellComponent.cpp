// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSpellComponent.h"

#include "DrawDebugHelpers.h"
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

	DamageTimer += DeltaTime;
	if(DamageTimer > 1.f)
	{
		HandleCollision();
		DamageTimer = 0;
	}

	Timer += DeltaTime;
	if(Timer > FireDuration)
	{
		if(!ensure(Particlesystem != nullptr))
		{
			return;
		}
		//TODO Add overlapcomponent and resize it depending on parameterblock size
 		Particlesystem->DeactivateSystem();
		SetComponentTickEnabled(false);
	}
}

void UFireSpellComponent::IncinerateTarget(float Duration)
{
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FireDuration = Duration;
	
	if(Character != nullptr)
	{
		Timer = 0;
		DamageTimer = 0;
		Particlesystem = UGameplayStatics::SpawnEmitterAttached(PSComponent->Template, Character->GetRootComponent(),NAME_None,   Character->GetActorLocation());
		Particlesystem->SetRelativeLocation(FVector(0,0,0));
		
	}
	if(MeshComponent != nullptr)
	{
		Timer = 0;
		DamageTimer = 0;
		Particlesystem = UGameplayStatics::SpawnEmitterAttached(PSComponent->Template, MeshComponent,NAME_None, MeshComponent->GetComponentLocation());
		Particlesystem->SetRelativeLocation(FVector(0,0,0));
		//TODO Reactivate partticles instead of creating a new one each time

	}
}

void UFireSpellComponent::HandleCollision()
{
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> IgnoreActors;

	if(Character != nullptr)
	{
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Character->GetActorLocation(), FMath::Square(200), TraceObjectTypes, nullptr, IgnoreActors, OverlappedActors);		
	}
	if(MeshComponent != nullptr)
	{
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MeshComponent->GetComponentLocation(), FMath::Square(20), TraceObjectTypes, nullptr, IgnoreActors, OverlappedActors);		
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("We HEar YoU %s"), *OverlappedActors[0]->GetName()));
		DrawDebugSphere(GetWorld(), MeshComponent->GetComponentLocation(), FMath::Square(20), 6, FColor::Red, false, 3.f);
	}

}

