// Fill out your copyright notice in the Description page of Project Settings.

#include "GunCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGunCharacter::AGunCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator().0f, -90.0f, 0.0f)));

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
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 360.0f, FColor::Red, TEXT("GunCharacter BeginPlay 3"));
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

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!Input) return;
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGunCharacter::Shoot);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AGunCharacter::DoJump);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGunCharacter::Move);
}

void AGunCharacter::Shoot(const FInputActionValue& Value)
{
	//if (!Value.Get<bool>()) return;
	check(GEngine != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("IA_Shoot triggered"));
	
}

void AGunCharacter::DoJump(const FInputActionValue& Value)
{
	Jump();	
}

void AGunCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	FVector2D FloatValue = Value.Get<FVector2D>();
	//if (FloatValue.IsZero()) return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, FloatValue.X);






	check(GEngine != nullptr);
	if (FloatValue.Length() > 0.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("IA_Move triggered: %f, %f"), FloatValue.X, FloatValue.Y);
	}
}