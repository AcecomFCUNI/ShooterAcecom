// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SA_WeaponBase.h"
#include "SA_RangedWeapon.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SHOOTERACECOM_API USA_RangedWeapon : public USA_WeaponBase {
	GENERATED_BODY()
	
	virtual void WeaponAction() override;
	
	UFUNCTION()
	virtual void Fire();

public:

	USA_RangedWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ShootRange;
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void AttachWeapon(AShooterAcecomCharacter* TargetCharacter);
};
