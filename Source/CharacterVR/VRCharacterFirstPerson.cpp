// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacterFirstPerson.h"
#include "CharacterVR.h"
/* VR Includes */
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AVRCharacterFirstPerson::AVRCharacterFirstPerson()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(RootComponent);
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	VRCamera->bUsePawnControlRotation = true;
	VRCamera->bLockToHmd = true;
	VRCamera->SetupAttachment(VROrigin);

	LeftHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left_Controller"));
	LeftHandComponent->SetupAttachment(VROrigin);
	LeftHandComponent->Hand = EControllerHand::Left;

	RightHandComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right_Controller"));
	RightHandComponent->SetupAttachment(VROrigin);
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


}

// Called when the game starts or when spawned
void AVRCharacterFirstPerson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCharacterFirstPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacterFirstPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	//PlayerInputComponent->BindAxis("MoveForward", this, &AVRCharacterFirstPerson::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AVRCharacterFirstPerson::MoveRight);
	//PlayerInputComponent->BindAxis("Turn", this, &AVRCharacterFirstPerson::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &AVRCharacterFirstPerson::AddControllerPitchInput);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVRCharacterFirstPerson::OnStartJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &AVRCharacterFirstPerson::OnStopJump);

}

//void AVRCharacterFirstPerson::MoveForward(float Value)
//{
//	if ((Controller != NULL) && (Value != 0.0f))
//	{
//		// find out which way is forward
//		FRotator Rotation = Controller->GetControlRotation();
//		// Limit pitch when walking or falling
//		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
//		{
//			Rotation.Pitch = 0.0f;
//		}
//		// add movement in that direction
//		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
//		AddMovementInput(Direction, Value);
//	}
//}
//
//void AVRCharacterFirstPerson::MoveRight(float Value)
//{
//	if ((Controller != NULL) && (Value != 0.0f))
//	{
//		// find out which way is right
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
//		// add movement in that direction
//		AddMovementInput(Direction, Value);
//	}
//}
//
//void AVRCharacterFirstPerson::OnStartJump()
//{
//	bPressedJump = true;
//}
//void AVRCharacterFirstPerson::OnStopJump()
//{
//	bPressedJump = false;
//}