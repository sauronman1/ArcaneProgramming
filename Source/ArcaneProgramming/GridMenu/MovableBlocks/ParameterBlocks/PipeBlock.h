// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParameterBlock.h"
#include "PipeBlock.generated.h"

/**
 * 
 */
UCLASS()
class ARCANEPROGRAMMING_API UPipeBlock : public UParameterBlock
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UWidget* PreviousNode;
	UPROPERTY()
	UWidget* NextNode;

	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	void SetNextAndPrevious(UWidget* TargetBlock);
private:
	UPROPERTY(EditAnywhere)
	bool HasNorth;
	UPROPERTY(EditAnywhere)
	bool HasSouth;
	UPROPERTY(EditAnywhere)
	bool HasEast;
	UPROPERTY(EditAnywhere)
	bool HasWest;
};
