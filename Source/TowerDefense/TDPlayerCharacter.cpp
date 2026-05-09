// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerCharacter.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

// Called every frame
void ATDPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Look);
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


