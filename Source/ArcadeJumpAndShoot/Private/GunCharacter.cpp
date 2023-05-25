// Fill out your copyright notice in the Description page of Project Settings.

#include "GunCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGunCharacter::AGunCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComp->SetupAttachment(GetMesh());
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	SpringArmComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void AGunCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	Jump();
}

void AGunCharacter::Move(const FInputActionValue& Value)
{
	check(GEngine != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("IA_Move triggered"));
	FVector2D FloatValue = Value.Get<FVector2D>();
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, FloatValue.X);
}