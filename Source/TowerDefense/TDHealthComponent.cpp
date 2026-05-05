// Fill out your copyright notice in the Description page of Project Settings.


#include "TDHealthComponent.h"

// Sets default values for this component's properties
UTDHealthComponent::UTDHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UTDHealthComponent::TakeDamage(float DamageAmount)
{
}

void UTDHealthComponent::OnDeath()
{
}

