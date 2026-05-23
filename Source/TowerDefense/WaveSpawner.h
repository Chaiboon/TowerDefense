// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATDEnemy.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

#include "WaveSpawner.generated.h"


UCLASS()
class TOWERDEFENSE_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	int32 TotalWaves = 3;
	UPROPERTY(EditAnywhere)
	int32 EnemiesPerWave = 5;
	UPROPERTY(EditAnywhere)
	float SpawnInterval = 2.0f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AATDEnemy> EnemyClass;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentWave = 0;
	UPROPERTY(VisibleAnywhere)
	int32 EnemiesSpawnedInCurrentWave = 0;
	UPROPERTY()
	ATDPlayerCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere)
	USoundBase* WaveStartSound;
	UPROPERTY()
	UAudioComponent* AudioComponent;

	void AddCountEnemyDeath();
private:
	UFUNCTION()
	void SpawnEnemy();
	FTimerHandle SpawnTimerHandle;
	UPROPERTY(VisibleAnywhere)
	int32 EnemyDeadCount = 0;
};
