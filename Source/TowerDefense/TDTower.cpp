// Fill out your copyright notice in the Description page of Project Settings.


#include "TDTower.h"
#include "ATDEnemy.h"


const FDamageEvent ATDTower::DamageType;

// Sets default values
ATDTower::ATDTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponenent"));
	SphereComponent->SetupAttachment(CapsuleComponent);

	

}

// Called when the game starts or when spawned
void ATDTower::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->SetSphereRadius(AttackRange);
	TowerLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ATDTower::AttackTick, AttackInterval, true);
}


int32 ATDTower::GetCost()
{
	return Cost;
}

void ATDTower::AttackTick()
{
	SphereComponent->GetOverlappingActors(EnemiesInRange, AATDEnemy::StaticClass());
	AATDEnemy* Target = Cast<AATDEnemy>(GetClosestEnemyInRange(EnemiesInRange));

	if (!Target) return;
	
	Target->TakeDamage(AttackDamage,DamageType,nullptr,this);
}

AActor* ATDTower::GetClosestEnemyInRange(TArray<AActor*> Enemies)
{
	if (Enemies.Num() == 0) return nullptr;
	float MinimunDistance = AttackRange;
	AActor* ClosestEnemy = nullptr;
	for (AActor* Enemy : Enemies) 
	{
		float Distance = FVector::Dist(TowerLocation, Enemy->GetActorLocation());
		MinimunDistance = FMath::Min(MinimunDistance, Distance);
		if (Distance == MinimunDistance) ClosestEnemy = Enemy;
	}
	return ClosestEnemy;
}

