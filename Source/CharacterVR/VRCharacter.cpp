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
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VROriginComp = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraOrigin"));
	VROriginComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	/* Assign to the VR origin component so any reset calls to the HMD can reset to 0,0,0 relative to this component */
	CameraComp->SetupAttachment(VROriginComp);

	// Motion Controllers
	LeftHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	LeftHandComponent->SetupAttachment(VROriginComp);
	LeftHandComponent->Hand = EControllerHand::Left;

	RightHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	RightHandComponent->SetupAttachment(VROriginComp);
	RightHandComponent->Hand = EControllerHand::Right;

	L_Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("L_Hand_SkeletalMesh"));
	L_Hand->SetupAttachment(LeftHandComponent);

	R_Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("R_Hand_SkeletalMesh"));
	R_Hand->SetupAttachment(RightHandComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skeletal_Hand_Asset(TEXT("SkeletalMesh'/Game/VirtualReality/Mannequin/Character/Mesh/MannequinHand_Right.MannequinHand_Right'"));
	if (Skeletal_Hand_Asset.Succeeded())
	{
		L_Hand->SetSkeletalMesh(Skeletal_Hand_Asset.Object);
		L_Hand->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		L_Hand->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
		L_Hand->SetRelativeScale3D(FVector(1.0f, -1.0f, 1.0f));

		R_Hand->SetSkeletalMesh(Skeletal_Hand_Asset.Object);
		R_Hand->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		R_Hand->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	}

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