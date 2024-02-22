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
class SHOOTERACECOM_API USA_WeaponBase : public USkeletalMeshComponent {
	GENERATED_BODY()

	UFUNCTION()
	virtual void WeaponAction();

protected:
	/** The Character holding this weapon*/

	AShooterAcecomCharacter* Character;
};
