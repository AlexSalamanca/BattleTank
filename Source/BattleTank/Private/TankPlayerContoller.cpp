// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerContoller.h"
#include "Tank.h"
#include "BattleTank.h"

ATank* ATankPlayerContoller::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

void ATankPlayerContoller::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Possesing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerContoller::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimsTowardsCrosshair();
}

void ATankPlayerContoller::AimsTowardsCrosshair() {
	if (!GetControlledTank())
		return;

	FVector HitLocation; //Put Parameter
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerContoller::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair in screen pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
		
	return true;
}

bool ATankPlayerContoller::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerContoller::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
