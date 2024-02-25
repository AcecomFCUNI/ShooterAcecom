// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon\SA_WeaponBase.h"

void ASA_WeaponBase::WeaponAction() {}

ASA_WeaponBase::ASA_WeaponBase()
{
	PivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot Component"));
	RootComponent = PivotComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(PivotComponent);
}