// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerContoller.h"


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