// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKDEMO_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public :
	void Rotate(float RotationSpeed);

	UPROPERTY(EditDefaultsOnly)
		float MaxDegreesPerSecond = 40;
};
