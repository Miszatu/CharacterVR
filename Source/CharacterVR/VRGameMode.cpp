// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGameMode.h"
#include "VRCharacter.h"
#include "ConstructorHelpers.h"
#include "UObject/ConstructorHelpers.h"

AVRGameMode::AVRGameMode(const FObjectInitializer& ObjectInitializer) : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BP_VRCharacter.BP_VRCharacter'"));

	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

void AVRGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();
}

