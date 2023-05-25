// Fill out your copyright notice in the Description page of Project Settings.

#include "GunCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AGunCharacter::AGunCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 360.0f, FColor::Red, TEXT("GunCharacter BeginPlay 3"));
	UE_LOG(LogTemp, Warning, TEXT("Hello world 2"));
}

// Called every frame
void AGunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupEnhancedInput(PlayerInputComponent);

	/*
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	//if (!PlayerController) return;
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{

		}
	}
	*/


	/*
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AGunCharacter::Shoot);

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), Priority);
			}
		}
	}
	*/
	
}

void AGunCharacter::SetupEnhancedInput(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController) return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!Subsystem) return;
	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!Input) return;
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGunCharacter::Shoot);
}

void AGunCharacter::Shoot(const FInputActionValue& Value)
{
	bool BoolValue = Value.Get<bool>();
	check(GEngine != nullptr);
	if (BoolValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Shoot triggered"));
	}
}