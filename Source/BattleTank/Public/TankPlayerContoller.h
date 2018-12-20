// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerContoller.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerContoller : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	
	
};
