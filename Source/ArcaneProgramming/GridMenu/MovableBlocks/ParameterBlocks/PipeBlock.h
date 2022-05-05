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
	UPipeBlock* PreviousNode;
	UPROPERTY()
	UPipeBlock* NextNode;
	UPROPERTY()
	USpellBlock* HeadNode;
	UPROPERTY()
	UParameterBlock* TailNode;

	UPROPERTY()
	TArray<int> Neighbours;
	
	virtual void NativeConstruct() override;
	virtual void UpdateNeighbours() override;
	void SetNextAndPrevious(UWidget* TargetBlock);
	void SetHeadForAll(USpellBlock* TargetBlock);
	void SetTailForAll(UParameterBlock* TargetBlock);

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
