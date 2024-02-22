// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SHOOTERACECOM_API UWeaponBase : public USkeletalMeshComponent {
	GENERATED_BODY()

	UFUNCTION()
	virtual void WeaponAction();
};
