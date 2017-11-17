// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "VRCharacterFirstPerson.generated.h"

UCLASS()
class CHARACTERVR_API AVRCharacterFirstPerson : public ACharacter
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scene)
		class USceneComponent * VROrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent * VRCamera;
	
	/* Motion Controllers */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		class UMotionControllerComponent* LeftHandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		class UMotionControllerComponent* RightHandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* R_Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* L_Hand;


	// Sets default values for this character's properties
	AVRCharacterFirstPerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//// Controls
	////handles moving forward/backward
	//UFUNCTION()
	//	void MoveForward(float Val);
	////handles strafing
	//UFUNCTION()
	//	void MoveRight(float Val);
	////sets jump flag when key is pressed
	//UFUNCTION()
	//	void OnStartJump();
	////clears jump flag when key is released
	//UFUNCTION()
	//	void OnStopJump();

};
