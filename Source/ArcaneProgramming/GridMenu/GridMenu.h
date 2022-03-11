#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "GridMenu.generated.h"

class UGridBlock;

UCLASS(ClassGroup = ("Custom Components"), meta = (BlueprintSpawnableComponent))
class UGridMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY()
	TArray<UGridBlock*> slots;
	
	void GetEmptySlots();
};