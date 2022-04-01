#include "MagePlayer.h"

#include "ArcaneProgramming/ArcaneGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ArcaneProgramming/MageHud.h"
#include "ArcaneProgramming/GridMenu/MovableBlocks/SpellBlocks/SpellBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AMagePlayer::AMagePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	//AutoPossessPlayer = EAutoRe

	bUseControllerRotationYaw = false;
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Cam->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Cam->SetRelativeLocation(FVector(0,0,40));
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
	PlayerInputComponent->BindAction("ActivateSpell",IE_Pressed,this, &AMagePlayer::ActivateSpell);
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
		float angle = Cam->GetRelativeRotation().Pitch + value;

		if(angle < 65.f && angle > -65.f)
			Cam->AddLocalRotation(FRotator(value,0,0));
	}
}

void AMagePlayer::Menu()
{
	MenuOn = !MenuOn;
	AArcaneGameModeBase* GameMode = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MenuOn)
	{
		GameMode->MageHud->MenuOn();
		APlayerController* Player = Cast<APlayerController>(GetController());
		if(Player)
		{
			Player->bShowMouseCursor = true;
			Player->bEnableClickEvents = true;
			Player->bEnableMouseOverEvents = true;
			Player->SetInputMode(FInputModeGameAndUI());

		}
	}
	if(!MenuOn)
	{
		GameMode->MageHud->MenuOff();
		APlayerController* Player = Cast<APlayerController>(GetController());
		if(Player && !MenuOn)
		{
			Player->bShowMouseCursor = false;
			Player->bEnableClickEvents = false;
			Player->bEnableMouseOverEvents = false;
			Player->SetInputMode(FInputModeGameOnly());

		}
	}
}

void AMagePlayer::ActivateSpell()
{
	GridMenu = Cast<AArcaneGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GridMenu;

	for(int i = 0; i<GridMenu->Slots.Num(); i++)
	{
		USpellBlock* SpellBlock = Cast<USpellBlock>(GridMenu->Slots[i]);
		if(SpellBlock != nullptr)
		{
			if(SpellBlock->IsPrimary)
			{
				SpellBlock->ActivateSpell();
			}
		}
	}
	
	for(int i = 0; i<GridMenu->Slots.Num(); i++)
	{
		USpellBlock* SpellBlock = Cast<USpellBlock>(GridMenu->Slots[i]);
		if(SpellBlock != nullptr)
		{
			if(!SpellBlock->IsPrimary)
			{
				SpellBlock->ActivateSpell();
			}
		}
	}
	

	
}






