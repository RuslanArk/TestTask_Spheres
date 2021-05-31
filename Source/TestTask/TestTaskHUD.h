// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestTaskHUD.generated.h"

UCLASS()
class ATestTaskHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestTaskHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};
