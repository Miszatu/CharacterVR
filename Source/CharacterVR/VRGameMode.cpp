// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGameMode.h"
#include "VRCharacter.h"
#include "ConstructorHelpers.h"
#include "UObject/ConstructorHelpers.h"

AVRGameMode::AVRGameMode(const FObjectInitializer& ObjectInitializer) : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Class'/Script/CharacterVR.VRCharacterFirstPerson'"));

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

