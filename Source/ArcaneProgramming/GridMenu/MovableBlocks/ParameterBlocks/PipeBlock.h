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
	UPROPERTY(EditAnywhere)
	bool HasNorth;
	UPROPERTY(EditAnywhere)
	bool HasSouth;
	UPROPERTY(EditAnywhere)
	bool HasEast;
	UPROPERTY(EditAnywhere)
	bool HasWest;
	
	UPROPERTY()
	UWidget* PreviousNode;
	UPROPERTY()
	UWidget* NextNode;

	virtual void UpdateNeighbours() override;
private:
	
};
