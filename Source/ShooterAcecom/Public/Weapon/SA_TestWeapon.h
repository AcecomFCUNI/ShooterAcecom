// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SA_RangedWeapon.h"
#include "SA_TestWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API USA_TestWeapon : public USA_RangedWeapon {
	GENERATED_BODY()

	virtual void Fire() override;
};
