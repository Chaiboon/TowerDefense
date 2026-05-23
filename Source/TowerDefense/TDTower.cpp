// Fill out your copyright notice in the Description page of Project Settings.


#include "TDTower.h"
#include "ATDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"


const FDamageEvent ATDTower::DamageType;

// Sets default values
ATDTower::ATDTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	BaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseComponent"));
	BaseComponent->SetupAttachment(CapsuleComponent);

	TurretComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretComponent"));
	TurretComponent->SetupAttachment(CapsuleComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponenent"));
	SphereComponent->SetupAttachment(CapsuleComponent);

	FireEffectRefferencePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FireEffectRefferencePoint"));
	FireEffectRefferencePoint->SetupAttachment(TurretComponent);

}

// Called when the game starts or when spawned
void ATDTower::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->SetSphereRadius(AttackRange);
	TowerLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ATDTower::AttackCooldown, AttackInterval, true);
}

void ATDTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereComponent->GetOverlappingActors(EnemiesInRange, AATDEnemy::StaticClass());
	AATDEnemy* Target = Cast<AATDEnemy>(GetClosestEnemyInRange(EnemiesInRange));
	if (!Target) return;

	FRotator CurrentRotation = TurretComponent->GetComponentRotation();
	FRotator TargetLocation = (Target->GetActorLocation() - this->GetActorLocation()).Rotation();
	FRotator RotationThisTick = FMath::RInterpTo(CurrentRotation, TargetLocation, DeltaTime, RotationSpeed);
	TurretComponent->SetWorldRotation(RotationThisTick);

	if (!bIsAttackable) return;
	
	if (AttackSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, Target->GetActorLocation());
	if (AttackEffect && FireEffectReffecencePoint) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), 
																			AttackEffect, 
																			FireEffectReffecencePoint->GetComponentLocation(), 
																			FireEffectReffecencePoint->GetComponentRotation());
	Target->TakeDamage(AttackDamage, DamageType, nullptr, this);
	bIsAttackable = false;
}


int32 ATDTower::GetCost()
{
	return Cost;
}

void ATDTower::AttackCooldown()
{
	bIsAttackable = true;
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

