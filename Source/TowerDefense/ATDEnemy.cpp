// Fill out your copyright notice in the Description page of Project Settings.


#include "ATDEnemy.h"

// Sets default values
AATDEnemy::AATDEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UTDHealthComponent>(TEXT("HealthComponent"));
	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePathComponent"));

	HealthComponent->team = ETDTeam::Enemy;
}

// Called when the game starts or when spawned
void AATDEnemy::BeginPlay()
{
	Super::BeginPlay();
	SplineLength = SplinePath->GetSplineLength();
	
}

// Called every frame
void AATDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SplinePath) return;
	DistanceAlongSpline += MoveSpeed * DeltaTime;
	FVector Location = SplinePath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
	FVector Rotation = SplinePath->GetDirectionAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
	SetActorLocation(Location);
	SetActorRotation(Rotation.Rotation());

	if (DistanceAlongSpline >= SplineLength) HandleDestroy();
	
}

float AATDEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthComponent->TakeDamage(DamageAmount, DamageCauser);
	return DamageAmount;
}

void AATDEnemy::HandleDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("Charactor's base take damage"));
	Destroy();
}

int32 AATDEnemy::GetGoldReward()
{
	return GoldReward;
}




