// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeJumpAndShootGameModeBase.h"

void AArcadeJumpAndShootGameModeBase::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Using ArcadeJumpAndShootGameModeBase"));
}