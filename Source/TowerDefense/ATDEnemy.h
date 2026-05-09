// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"
#include "TDHealthComponent.h"

#include "ATDEnemy.generated.h"

UCLASS()
class TOWERDEFENSE_API AATDEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATDEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplinePath;
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300.0f;
	UPROPERTY(VisibleAnywhere)
	float DistanceAlongSpline = 0.0f;
	UPROPERTY(VisibleAnywhere)
	UTDHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere)
	float SplineLength;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestroy();

};
