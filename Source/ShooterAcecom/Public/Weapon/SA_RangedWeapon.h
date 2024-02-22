// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "RangedWeapon.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SHOOTERACECOM_API URangedWeapon : public UWeaponBase {
	GENERATED_BODY()
	
	virtual void WeaponAction() override;

	UFUNCTION()
	virtual void Fire();
};
