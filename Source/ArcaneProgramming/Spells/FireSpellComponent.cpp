// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSpellComponent.h"

#include "DrawDebugHelpers.h"
#include "ArcaneProgramming/Player/MagePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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
		IgnoreActors.Empty();
 		Particlesystem->DeactivateSystem();
		//TODO if alternative not found use destroycomp and set var t null
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
		if(Particlesystem == nullptr)
		{
			Particlesystem = UGameplayStatics::SpawnEmitterAttached(PSComponent->Template, Character->GetRootComponent(),NAME_None,   Character->GetActorLocation());
			Particlesystem->SetRelativeLocation(FVector(0,0,0));
		}
		//TODO Destroy and recreate PS, will be replaced by Niagara in the future, change colour of manacost text when working, fix error colour and pipes update when removed
		if(Particlesystem->IsActive() == false)
			Particlesystem->Activate(true);
		
	}
	if(MeshComponent != nullptr)
	{
		Timer = 0;
		DamageTimer = 0;

		if(Particlesystem == nullptr)
		{
			Particlesystem = UGameplayStatics::SpawnEmitterAttached(PSComponent->Template, MeshComponent,NAME_None, MeshComponent->GetComponentLocation());
			Particlesystem->SetRelativeLocation(FVector(0,0,0));
		}
	}
}

void UFireSpellComponent::HandleCollision()
{
	AMagePlayer* Character = Cast<AMagePlayer>(GetOwner());
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> OverlappedActors;

	if(Character != nullptr)
	{
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Character->GetActorLocation(), FMath::Square(200), TraceObjectTypes, nullptr, IgnoreActors, OverlappedActors);		
	}
	if(MeshComponent != nullptr)
	{
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MeshComponent->GetComponentLocation(), FMath::Square(20), TraceObjectTypes, nullptr, IgnoreActors, OverlappedActors);

		for (auto OverlappedActor : OverlappedActors)
		{
			if(OverlappedActor != GetOwner())
			{
				UFireSpellComponent* FireSpellComponent = OverlappedActor->FindComponentByClass<UFireSpellComponent>();
				if(FireSpellComponent == nullptr)
				{
					FireSpellComponent = NewObject<UFireSpellComponent>(OverlappedActor, UFireSpellComponent::StaticClass());
					FireSpellComponent->RegisterComponent();
					FireSpellComponent->PSComponent = PSComponent;
				}
				else
				{
					Timer = 0;
					DamageTimer = 0;
					FireSpellComponent->SetComponentTickEnabled(true);	
				}

				FireSpellComponent->IncinerateTarget(FireDuration);
				FireSpellComponent->IgnoreActors.Add(GetOwner());
				IgnoreActors.Add(OverlappedActor);
				
			}
		}
		
		DrawDebugSphere(GetWorld(), MeshComponent->GetComponentLocation(), FMath::Square(20), 6, FColor::Red, false, 3.f);
	}

}

