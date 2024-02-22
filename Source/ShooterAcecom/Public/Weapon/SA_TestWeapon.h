// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangedWeapon.h"
#include "TestWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API UTestWeapon : public URangedWeapon {
	GENERATED_BODY()

	virtual void Fire() override;
};
