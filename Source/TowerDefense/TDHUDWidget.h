// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Gold;
	UPROPERTY(BlueprintReadOnly)
	int32 Lives;
	UPROPERTY(BlueprintReadOnly)
	int32 Wave;
	UFUNCTION(BlueprintCallable)
	void UpdateHUD(int32 NewGold, int32 NewLives, int32 NewWave);
};
