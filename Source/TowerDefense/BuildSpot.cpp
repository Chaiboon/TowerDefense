// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSpot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TDPlayerCharacter.h"

// Sets default values
ABuildSpot::ABuildSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ABuildSpot::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuildSpot::OnBoxOverlap);
}

void ABuildSpot::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA<ATDPlayerCharacter>()) return;
	if (bIsOccupied) return;

	if (ATDPlayerCharacter* PlayerCharacter = Cast<ATDPlayerCharacter>(OtherActor)) PlayerCharacter->AssignBuildable(this);
}

void ABuildSpot::SetIsOccupied(bool NewbIsOccupied)
{
	bIsOccupied = NewbIsOccupied;
}