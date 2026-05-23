// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerCharacter.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TDTower.h"

// Sets default values
ATDPlayerCharacter::ATDPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UTDHealthComponent>(TEXT("HealthComponent"));

	SpringArmComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ATDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) 
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	HUDWidget = CreateWidget<UTDHUDWidget>(PlayerController, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
		HUDWidget->UpdateHUD(Gold, Lives, CurrentWave);
	}

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
}

// Called to bind functionality to input
void ATDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(BuildAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Build);
	}
}

void ATDPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	FVector2D InputValue = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), InputValue.X * MoveSpeed);
	AddMovementInput(GetActorRightVector(), InputValue.Y * MoveSpeed);
}

void ATDPlayerCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller) return;

	FVector2D InputValue = Value.Get<FVector2D>();
	AddControllerYawInput(InputValue.X * LookSensitivity);
	AddControllerPitchInput(InputValue.Y * LookSensitivity * -1);
}

void ATDPlayerCharacter::Build(const FInputActionValue& Value)
{
	if (!Controller) return;
	if (!Buildable) return;

	FTransform SpawnLocation = Buildable->GetActorTransform();
	if (ATDTower* SpawnedTower = GetWorld()->SpawnActor<ATDTower>(TowerClass, SpawnLocation))
	{
		int32 Cost = SpawnedTower->GetCost();
		if (Gold >= Cost)
		{
			SpendGold(Cost);
			Buildable->SetIsOccupied(true);
			Buildable = nullptr;
		}
		else
		{
			SpawnedTower->Destroy();
		}
	}
}

void ATDPlayerCharacter::AddGold(int32 AddedGold)
{
	Gold += AddedGold;
	if (HUDWidget) HUDWidget->UpdateHUD(Gold, Lives, CurrentWave);
}

void ATDPlayerCharacter::SpendGold(int32 SpentGold)
{
	Gold -= SpentGold;
	if (HUDWidget) HUDWidget->UpdateHUD(Gold, Lives, CurrentWave);
}

void ATDPlayerCharacter::AssignBuildable(ABuildSpot* BuildableArea)
{
	this->Buildable = BuildableArea;
}

void ATDPlayerCharacter::SetLives(int32 newLives)
{
	Lives = newLives;
}

void ATDPlayerCharacter::LoseLife()
{
	Lives--;
	if (HUDWidget) HUDWidget->UpdateHUD(Gold, Lives, CurrentWave);
	if (Lives <= 0) ShowGameOver(false);
}

int32 ATDPlayerCharacter::GetLives()
{
	return Lives;
}

int32 ATDPlayerCharacter::GetCurrentWave()
{
	return CurrentWave;
}

void ATDPlayerCharacter::SetCurrentWave(int32 newWave)
{
	CurrentWave = newWave;
	if (HUDWidget) HUDWidget->UpdateHUD(Gold, Lives, CurrentWave);
}

void ATDPlayerCharacter::SetGold(int32 newGold)
{
	Gold = newGold;
	if (HUDWidget) HUDWidget->UpdateHUD(Gold, Lives, CurrentWave);
}

void ATDPlayerCharacter::ShowGameOver(bool bWon)
{
	GameOverWidget = CreateWidget<UTDGameOverWidget>(PlayerController, GameOverWidgetClass);
	if (GameOverWidget)
	{
		GameOverWidget->bDidWin = bWon;
		GameOverWidget->AddToViewport();

		if (bWon && VictorySound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), VictorySound, GetActorLocation());
		if (!bWon && DefeatSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefeatSound, GetActorLocation());

		PlayerController->bShowMouseCursor = true;
		PlayerController->FlushPressedKeys();
		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}


