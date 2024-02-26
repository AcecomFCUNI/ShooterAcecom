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

	/** Pivot for Rotation*/
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* PivotComponent;

	/** Mesh Component*/
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UFUNCTION()
	virtual void WeaponAction();
	
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
public:

	ASA_WeaponBase();
	

};
