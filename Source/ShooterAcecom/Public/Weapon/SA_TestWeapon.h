// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SA_RangedWeapon.h"
#include "SA_TestWeapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERACECOM_API ASA_TestWeapon : public ASA_RangedWeapon {
	GENERATED_BODY()
	
public:
	 ASA_TestWeapon();
	
};
