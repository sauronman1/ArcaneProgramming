#pragma once

#include "Coreminimal.h"

#include "CustomButton.h"
#include "GridMenu.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "GridBlock.generated.h"

class UButton;
UCLASS()
class UGridBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	bool MenuSet = false;
	
	UPROPERTY(VisibleAnywhere)
	int Left;
	UPROPERTY(VisibleAnywhere)
	int Right;
	UPROPERTY(VisibleAnywhere)
	int Up;
	UPROPERTY(VisibleAnywhere)
	int Down;
	
	UPROPERTY(EditAnywhere)
	int SlotID;
	UPROPERTY(meta = (BindWidget))
	UImage* SlotImage;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UniGrid;
	UPROPERTY(meta = (BindWidget))
	UCustomButton* CustomGridButton;

	UFUNCTION()
	void ClickAndDrop();
	
};