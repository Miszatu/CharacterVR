// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

#include "VRCharacter.generated.h"

UCLASS()
class CHARACTERVR_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UCameraComponent* CameraComp;

	/* Component to specify origin for the HMD */
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* VROriginComp;

	UPROPERTY(EditDefaultsOnly, Category = "VR")
		bool bPositionalHeadTracking;

	/* Motion Controllers */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		class UMotionControllerComponent* LeftHandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		class UMotionControllerComponent* RightHandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* R_Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* L_Hand;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Controls
	//handles moving forward/backward
	UFUNCTION()
		void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
		void MoveRight(float Val);
	//sets jump flag when key is pressed
	UFUNCTION()
		void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
		void OnStopJump();

	FVector LeftPos;
	FVector RightPos;
	// Resets HMD Origin position and orientation 
	//UFUNCTION()
	//void ResetHMDOrigin();

	//// Toggle between Seated and Standing VR Tracking 
	//UFUNCTION()
	//void ToggleTrackingSpace();
};
