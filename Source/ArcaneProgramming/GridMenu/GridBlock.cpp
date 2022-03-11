#include "GridBlock.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"

void UGridBlock::NativeConstruct()
{
	gridPanel = Cast<UGridPanel>(GetParent());
	if(ButtonObj){ButtonObj->OnClicked.AddDynamic(this, &UGridBlock::GetPanel);}
}

void UGridBlock::GetPanel()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *gridPanel->GetName());
}

