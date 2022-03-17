#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MagePlayer.generated.h"

UCLASS()
class AMagePlayer : public ACharacter
{
    GENERATED_BODY()
public:
    AMagePlayer();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:

    bool MenuOn = false;
    
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* Cam;
    
    void HoriMove(float value);
    void VertiMove(float value);
    void HoriRot(float value);
    void VertiRot(float value);
    void Menu();

    
};