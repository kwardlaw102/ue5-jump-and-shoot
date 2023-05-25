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
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 360.0f, FColor::Red, TEXT("GunCharacter BeginPlay 3"));
	//UE_LOG(LogTemp, Warning, TEXT("Hello world 2"));
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
}

void AGunCharacter::SetupEnhancedInput(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController) return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!Subsystem) return;
	Subsystem->AddMappingContext(InputMappingContext, 0);

	if (!ShootAction) UE_LOG(LogTemp, Warning, TEXT("ShootAction is missing; character may not behave properly"));
	if (!JumpAction) UE_LOG(LogTemp, Warning, TEXT("JumpAction is missing; character may not behave properly"));
	if (!MoveAction) UE_LOG(LogTemp, Warning, TEXT("MoveAction is missing; character may not behave properly"));

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!Input) return;
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGunCharacter::Shoot);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGunCharacter::Move);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AGunCharacter::DoJump);
}

void AGunCharacter::Shoot(const FInputActionValue& Value)
{
	check(GEngine != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("IA_Shoot triggered"));
}

void AGunCharacter::DoJump(const FInputActionValue& Value)
{
	check(GEngine != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("IA_Jump triggered"));
}

void AGunCharacter::Move(const FInputActionValue& Value)
{
	check(GEngine != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("IA_Move triggered"));
}