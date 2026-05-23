// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"

#include "TDTower.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretComponent;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* FireEffectRefferencePoint;
	UPROPERTY(EditAnywhere)
	float AttackRange = 500.0f;
	UPROPERTY(EditAnywhere)
	float AttackDamage = 10.0f;
	UPROPERTY(EditAnywhere)
	float AttackInterval = 1.0f;
	UPROPERTY(VisibleAnywhere)
	FVector TowerLocation;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> EnemiesInRange;
	UPROPERTY(EditAnywhere)
	USoundBase* AttackSound;
	int32 GetCost();
	static const FDamageEvent DamageType;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 3.0f;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* AttackEffect;
private:
	UPROPERTY(EditAnywhere)
	int32 Cost = 50;
	bool bIsAttackable = true;
	FTimerHandle AttackTimerHandle;
	void AttackCooldown();
	AActor* GetClosestEnemyInRange(TArray<AActor*> Enemies);
};
