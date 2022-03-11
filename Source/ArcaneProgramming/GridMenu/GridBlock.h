#pragma once

#include "Coreminimal.h"

#include "GridMenu.h"
#include "Blueprint/UserWidget.h"
#include "GridBlock.generated.h"

class UButton;
class UGridPanel;
UCLASS()
class UGridBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	UGridPanel* gridPanel;
	UPROPERTY(EditAnywhere)
	int MyID;
	UPROPERTY(EditAnywhere)
	FVector4 Neighbours;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonObj;

	UFUNCTION()
	void GetPanel();
};