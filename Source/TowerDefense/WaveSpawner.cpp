// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"
#include "TimerManager.h"
#include "ATDEnemy.h"

// Sets default values
AWaveSpawner::AWaveSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this, &AWaveSpawner::SpawnEnemy, SpawnInterval, true);
}

void AWaveSpawner::AddCountEnemyDeath()
{
	EnemyDeadCount++;
	if (EnemyDeadCount >= EnemiesPerWave)
	{
		EnemyDeadCount = 0;
		CurrentWave++;
		if (CurrentWave >= TotalWaves)
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		}
		else
		{
			GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveSpawner::SpawnEnemy, SpawnInterval, true);
		}
	}
}

void AWaveSpawner::SpawnEnemy()
{
	if (!EnemyClass) return;

	if (AATDEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AATDEnemy>(EnemyClass, GetActorTransform()))
	{
		EnemiesSpawnedInCurrentWave++;
		if (EnemiesSpawnedInCurrentWave >= EnemiesPerWave)
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
			EnemiesSpawnedInCurrentWave = 0;
		}
	}
}


