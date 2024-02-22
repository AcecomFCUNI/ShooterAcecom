// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API UMeleeWeapon : public UWeaponBase {
	GENERATED_BODY()

	virtual void WeaponAction() override;
};
