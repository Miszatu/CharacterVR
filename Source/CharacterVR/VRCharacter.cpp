// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "CharacterVR.h"
/* VR Includes */
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VROriginComp = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraOrigin"));
	VROriginComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	/* Assign to the VR origin component so any reset calls to the HMD can reset to 0,0,0 relative to this component */
	CameraComp->SetupAttachment(VROriginComp);

	LeftHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHandComponent->Hand = EControllerHand::Left;
	LeftHandComponent->Activate(true);
	LeftHandComponent->SetupAttachment(VROriginComp);

	L_Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("L_Hand"));
	L_Hand->SetOnlyOwnerSee(true);
	L_Hand->SetupAttachment(LeftHandComponent);
	L_Hand->RelativeRotation = FRotator(0.0f, 0.0f, -90.0f);
	L_Hand->RelativeScale3D = FVector(1.0f, -1.0f, 1.0f);
	L_Hand->RelativeLocation = FVector(20.0f, 0.0f, 0.0f);

	RightHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHandComponent->Hand = EControllerHand::Right;
	RightHandComponent->Activate(true);
	RightHandComponent->SetupAttachment(VROriginComp);

	R_Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("R_Hand"));
	R_Hand->SetOnlyOwnerSee(true);
	R_Hand->SetupAttachment(RightHandComponent);
	R_Hand->RelativeRotation = FRotator(0.0f, 0.0f, 90.0f);
	R_Hand->RelativeLocation = FVector(20.0f, 0.0f, 0.0f);
	FVector LeftPos = L_Hand->GetComponentLocation();
	FVector RightPos = R_Hand->GetComponentLocation();

	bPositionalHeadTracking = false;
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
	UE_LOG(LogTemp, Log, TEXT("Left Position is %s"), *LeftPos.ToString());
	UE_LOG(LogTemp, Log, TEXT("Right Position is %s"), *RightPos.ToString());
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
//	PlayerInputComponent->BindAction("ResetHMDOrigin", IE_Pressed, this, &AVRCharacter::ResetHMDOrigin);
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

//void AVRCharacter::ResetHMDOrigin()
//{
//	IHeadMountedDisplay* HMD = (IHeadMountedDisplay*)(GEngine->HMDDevice.Get());
//	if (HMD && HMD->IsStereoEnabled())
//	{
//		HMD->ResetOrientationAndPosition();
//	}
//}