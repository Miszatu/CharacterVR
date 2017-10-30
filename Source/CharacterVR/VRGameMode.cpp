// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGameMode.h"
#include "VRCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVRGameMode::AVRGameMode(const FObjectInitializer& ObjectInitializer) : Super()
{
	DefaultPawnClass = AVRCharacter::StaticClass();
}

void AVRGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();
}

