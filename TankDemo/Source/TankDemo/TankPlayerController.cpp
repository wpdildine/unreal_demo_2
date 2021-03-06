// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "TankDemo.h"


//Tick
	//Super
	//AimToCrosshair

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrossHair();
		
}

void ATankPlayerController::AimTowardsCrossHair()

{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	FVector HitLocation;
	if (!ensure(GetPawn())){return;}

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {


	
		int32 ViewPortSizeX, ViewPortSizeY;
		GetViewportSize(ViewPortSizeX, ViewPortSizeY);
		float PixelCoordinateX = ViewPortSizeX * CrossHairX;
		float PixelCoordinateY = ViewPortSizeY * CrossHairY;

		auto ScreenLocation = FVector2D(PixelCoordinateX, PixelCoordinateY);
		FVector LookDirection;
		if (GetLookDirection(ScreenLocation, LookDirection)) {
			//UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *LookDirection.ToString());
		};
		
		if (GetLookDirection(ScreenLocation, LookDirection))
		{
			return GetLookVectorHitLocation(LookDirection, HitLocation);
		}

		return false;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const 
{
	
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
	//UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *WorldDirection.ToString());
	
	return true;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult OutHit;
	FCollisionQueryParams Parameters;
	FCollisionResponseParams Response;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto End = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, End, ECC_Visibility, Parameters, Response))
	{
		HitLocation = OutHit.Location;
		//UE_LOG(LogTemp, Warning, TEXT("HIT %s"), *HitLocation.ToString());
		return true;
	}
	HitLocation = FVector(0);
	//UE_LOG(LogTemp, Warning, TEXT("HIT %s"), *HitLocation.ToString());

	return false;

	


}
