// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon\SA_WeaponBase.h"

#include "Camera/CameraComponent.h"

void ASA_WeaponBase::WeaponAction() {}

ASA_WeaponBase::ASA_WeaponBase()
{
	PivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot Component"));
	RootComponent = PivotComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(PivotComponent);
}

void ASA_WeaponBase::TickActor(float DeltaTime, ELevelTick TickType,FActorTickFunction& ThisTickFunction) {
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	//rotate weapon if its attached
	if(Character != nullptr) {
		FRotator newRotation = FRotator(0.0f, 0.0f, Character->GetCameraComponent()->GetRelativeRotation().Pitch * -1);
		FQuat quatRotation = FQuat(newRotation);
		SetActorRelativeRotation(quatRotation);
	}
		
}


