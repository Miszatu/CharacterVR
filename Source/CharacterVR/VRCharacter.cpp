// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVRCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AVRCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AVRCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVRCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AVRCharacter::OnStopJump);
	//PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AVRCharacter::MotionControlLeftTriggerPressed);
	//PlayerInputComponent->BindAction("MoveForward", IE_Released, this, &AVRCharacter::MotionControlLeftTriggerReleased);


}

void AVRCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AVRCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AVRCharacter::OnStartJump()
{
	bPressedJump = true;
}
void AVRCharacter::OnStopJump()
{
	bPressedJump = false;
}
//
//// Left Trigger Press
//void AVRCharacter::MotionControlLeftTriggerPressed()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Left trigger is PRESSED"));
//}
//
//// Left Trigger Release
//void AVRCharacter::MotionControlLeftTriggerReleased()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Left trigger is RELEASED"));
//}
//
//// Right Trigger Press
//void AVRCharacter::MotionControlRightTriggerPressed()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Right trigger is PRESSED"));
//}
//
//// Right Trigger Release
//void AVRCharacter::MotionControlRightTriggerReleased()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Right trigger is RELEASED"));
//}