#include "MagePlayer.h"

AMagePlayer::AMagePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	//AutoPossessPlayer = EAutoRe

	bUseControllerRotationYaw = false;
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachTo(RootComponent);
	cam->SetRelativeLocation(FVector(0,0,40));
}

void AMagePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMagePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMagePlayer::HoriMove);
	PlayerInputComponent->BindAxis("Vertical", this, &AMagePlayer::VertiMove);
	
	PlayerInputComponent->BindAxis("HoriRot", this, &AMagePlayer::HoriRot);
	PlayerInputComponent->BindAxis("VertiRot", this, &AMagePlayer::VertiRot);
	
	PlayerInputComponent->BindAction("Menu",IE_Pressed,this, &AMagePlayer::Menu);

}

void AMagePlayer::HoriMove(float value)
{
	if(value && !MenuOn)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AMagePlayer::VertiMove(float value)
{
	if(value && !MenuOn)
	{
		AddMovementInput(GetActorForwardVector(), value);

	}
}

void AMagePlayer::HoriRot(float value)
{
	if(value && !MenuOn)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AMagePlayer::VertiRot(float value)
{
	if(value && !MenuOn)
	{
		float angle = cam->GetRelativeRotation().Pitch + value;

		if(angle < 65.f && angle > -65.f)
			cam->AddLocalRotation(FRotator(value,0,0));
	}
}

void AMagePlayer::Menu()
{
	MenuOn = !MenuOn;
}







