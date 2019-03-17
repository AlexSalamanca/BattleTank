// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerContoller.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerContoller : public APlayerController
{
	GENERATED_BODY()
//change to private
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	void AimsTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
