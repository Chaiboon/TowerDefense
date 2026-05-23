// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "TDHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "ETDTeam.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "BuildSpot.h"
#include "TDHUDWidget.h"
#include "TDGameOverWidget.h"
#include "TDTower.h"

#include "TDPlayerCharacter.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(VisibleAnywhere)
	UTDHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	ETDTeam Team = ETDTeam::Friendly;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere,Category = "Input")
	UInputAction* BuildAction;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300.0f;
	UPROPERTY(EditAnywhere)
	float LookSensitivity = 0.3f;
	UPROPERTY(VisibleAnywhere)
	ABuildSpot* Buildable;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTDHUDWidget> HUDWidgetClass;
	UPROPERTY()
	UTDHUDWidget* HUDWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTDGameOverWidget> GameOverWidgetClass;
	UPROPERTY()
	UTDGameOverWidget* GameOverWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDTower> TowerClass;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Build(const FInputActionValue& Value);
	void AddGold(int32 AddedGold);
	void SpendGold(int32 SpentGold);
	void AssignBuildable(ABuildSpot* BuildableArea);
	void SetLives(int32 newLives);
	void LoseLife();
	int32 GetLives();
	int32 GetCurrentWave();
	void SetCurrentWave(int32 newWave);
	void SetGold(int32 newGold);
	void ShowGameOver(bool bWon);
private:
	UPROPERTY(EditAnywhere)
	int32 Gold = 100;
	UPROPERTY(EditAnywhere)
	int32 Lives = 3;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentWave = 1;
};
