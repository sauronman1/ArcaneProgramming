#pragma once
#include "CoreMinimal.h"

#include "ArcaneProgramming/GridMenu/GridMenu.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MagePlayer.generated.h"

class UGridMenu;

UCLASS()
class AMagePlayer : public ACharacter
{
    GENERATED_BODY()
public:
    AMagePlayer();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:

    bool MenuOn = false;
    
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* Cam;
    UPROPERTY()
    UGridMenu* GridMenu;
    
    void HoriMove(float value);
    void VertiMove(float value);
    void HoriRot(float value);
    void VertiRot(float value);
    void Menu();
    void ActivateSpell();

    
};