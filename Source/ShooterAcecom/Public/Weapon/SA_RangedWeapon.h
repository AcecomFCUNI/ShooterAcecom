// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SA_WeaponBase.h"
#include "SA_RangedWeapon.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SHOOTERACECOM_API ASA_RangedWeapon : public ASA_WeaponBase {
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bIsFiring;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool bCanFire;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bIsSemiAutomatic = false;

	UPROPERTY(EditDefaultsOnly)
	bool bFiredOnce = false;

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

public:
	ASA_RangedWeapon();

protected:

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	virtual void WeaponAction() override;
	
	UFUNCTION()
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReleaseFire();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void AttachWeapon(AShooterAcecomCharacter* TargetCharacter);
};
