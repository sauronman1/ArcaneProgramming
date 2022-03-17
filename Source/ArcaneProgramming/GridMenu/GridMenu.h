#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"

#include "GridMenu.generated.h"

class USpellBlock;
class UGridBlock;
class UGridPanel;

UCLASS(ClassGroup = ("Custom Components"), meta = (BlueprintSpawnableComponent))
class UGridMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UGridPanel* GridBlockPanel;
	UPROPERTY()
	TArray<UUserWidget*> Slots; 
	UPROPERTY()
	USpellBlock* SelectedSpellBlock;

	void SetSlotInArray(UUserWidget* Block, int SlotID);
	void SetEmptySlots();
};