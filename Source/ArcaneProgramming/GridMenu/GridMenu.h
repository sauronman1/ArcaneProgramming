#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "MovableBlocks/ParameterBlocks/ParameterBlock.h"

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
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaPoolDisplay;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaCostDisplay;
	UPROPERTY(meta = (BindWidget))
	UCustomButton* ChannelButton;
	
	UPROPERTY()
	TMap<int, UWidget*> Slots; 
	UPROPERTY()
	UUserWidget* SelectedBlock;
	UPROPERTY(EditAnywhere)
	int ManaPool;;

	int ManaCost = 0;
	int DurationToCostConversion = 10;
	int AmplifierToCostConversion = 100;
	bool MenuSet = false;

	void SetSlotInArray(UUserWidget* InBlock, int SlotID, bool RemoveBlock);
	void SetEmptySlots();
	void ShowManaCost();

	UFUNCTION()
	void UpdateNeigboursOnAllNodes();
	UFUNCTION()
	void NullifyAllPipes();
};