// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ShooterAcecom/ShooterAcecomCharacter.h"
#include "SA_WeaponBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SHOOTERACECOM_API ASA_WeaponBase : public AActor {
	GENERATED_BODY()

protected:
	/** The Character holding this weapon*/
	UPROPERTY()
	AShooterAcecomCharacter* Character;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* PivotComponent;

	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UFUNCTION()
	virtual void WeaponAction();

public:

	ASA_WeaponBase();
	

};
