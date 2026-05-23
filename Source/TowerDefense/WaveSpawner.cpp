// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"
#include "TimerManager.h"
#include "ATDEnemy.h"
#include "Kismet/GameplayStatics.h"

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
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDPlayerCharacter::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0) PlayerCharacter = Cast<ATDPlayerCharacter>(FoundActors[0]);
	if (PlayerCharacter) PlayerCharacter->SetCurrentWave(CurrentWave+1);
}

void AWaveSpawner::AddCountEnemyDeath()
{
	EnemyDeadCount++;
	if (EnemyDeadCount >= EnemiesPerWave)
	{
		if (AudioComponent) AudioComponent->Stop();
		EnemyDeadCount = 0;
		CurrentWave++;
		
		if (CurrentWave >= TotalWaves)
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
			if (PlayerCharacter) PlayerCharacter->ShowGameOver(true);
		}
		else
		{
			if (PlayerCharacter) PlayerCharacter->SetCurrentWave(CurrentWave+1);
			GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveSpawner::SpawnEnemy, SpawnInterval, true);
		}
	}
}

void AWaveSpawner::SpawnEnemy()
{
	if (!EnemyClass) return;
	if (EnemiesSpawnedInCurrentWave == 0)
	{
		if(WaveStartSound) AudioComponent = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WaveStartSound, GetActorLocation());
	}

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


