// Fill out your copyright notice in the Description page of Project Settings.

#include "TDHealthComponent.h"
#include "TDPlayerCharacter.h"
#include "ATDEnemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTDHealthComponent::UTDHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTDHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	// ...
	
}


// Called every frame
void UTDHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTDHealthComponent::TakeDamage(float DamageAmount, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0.0f) OnDeath();
}

void UTDHealthComponent::OnDeath()
{
	if (AActor* Owner = GetOwner())
	{
		if (ATDPlayerCharacter* Player = Cast<ATDPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			if (AATDEnemy* Enemy = Cast<AATDEnemy>(Owner))
			{
				Player->AddGold(Enemy->GetGoldReward());
			}
		}
		Owner->Destroy();
	}
}

