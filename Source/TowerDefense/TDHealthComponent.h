// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ETDTeam.h"

#include "TDHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTDHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ETDTeam team;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TakeDamage(float DamageAmount, AActor* DamageCauser);
	void OnDeath();
		
};
