// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool bDidWin;
	UFUNCTION(BlueprintCallable)
	void RestartGame();
};
