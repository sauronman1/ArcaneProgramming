#pragma once

#include "Coreminimal.h"

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

	UPROPERTY(EditAnywhere)
	int SlotID;
	UPROPERTY(EditAnywhere)
	FVector4 Neighbours;
	UPROPERTY(meta = (BindWidget))
	UImage* SlotImage;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UniGrid;
	
	UFUNCTION()
	void GetPanel();
	
};