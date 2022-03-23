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
	TMap<int, UWidget*> Slots; 
	UPROPERTY()
	USpellBlock* SelectedSpellBlock;

	bool MenuSet = false;

	void SetSlotInArray(UUserWidget* InBlock, int SlotID, bool RemoveBlock);
	void SetEmptySlots();
};