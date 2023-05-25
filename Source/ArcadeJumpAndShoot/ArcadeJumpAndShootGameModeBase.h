// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcadeJumpAndShootGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEJUMPANDSHOOT_API AArcadeJumpAndShootGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;

};
