// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon\SA_RangedWeapon.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAcecom/ShooterAcecomCharacter.h"

ASA_RangedWeapon::ASA_RangedWeapon() {
	PrimaryActorTick.bCanEverTick = true;
	bCanFire = true;
}

void ASA_RangedWeapon::TickActor(float DeltaTime, ELevelTick TickType,
	FActorTickFunction& ThisTickFunction) {
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	Fire();
}


void ASA_RangedWeapon::WeaponAction() {
	Fire();
} 

void ASA_RangedWeapon::Fire() {
	if (Character == nullptr || Character->GetController() == nullptr) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("WeaponAction2"))

	if(!bIsFiring || !bCanFire){
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("WeaponAction1"))

	bCanFire = false;
	FTimerHandle TimerHandler;

	GetWorld()->GetTimerManager().SetTimer(TimerHandler, [&] {
		bCanFire = true;
	}, FireRate, false);

	FVector foward = Character->GetCameraComponent()->GetForwardVector();
	FVector start = Character->GetCameraComponent()->GetComponentToWorld().GetLocation() + foward * 50;
	FVector end = start + foward * ShootRange;
	FHitResult hit;

	if(GetWorld()) {
		bool actorHit = GetWorld()->LineTraceSingleByChannel(
			hit,
			start,
			end,
			ECC_Pawn,
			FCollisionQueryParams(),
			FCollisionResponseParams());
		DrawDebugLine(GetWorld(), start, end, FColor::Blue, false, 2, 0, 10);
		if(actorHit && hit.GetActor()) {
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, hit.GetActor()->GetFName().ToString());
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr) {
		// // Get the animation object for the arms mesh
		// UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		// if (AnimInstance != nullptr){
		// 	AnimInstance->Montage_Play(FireAnimation, 1.f);
		// }
	}
}

void ASA_RangedWeapon::SetFire(){
	bIsFiring = true;
}

void ASA_RangedWeapon::ReleaseFire(){
	UE_LOG(LogTemp, Warning, TEXT("Release"));
	bIsFiring = false;
}

void ASA_RangedWeapon::AttachWeapon(AShooterAcecomCharacter* TargetCharacter) {
	Character = TargetCharacter;
	if (Character == nullptr) {
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Character->GetMesh()->GetChildComponent(0)->GetName());
	
	Character->GetMesh()->GetChildComponent(0)->SetRelativeLocation(FVector(21, 17, 40));
	Character->GetMesh()->GetChildComponent(0)->SetRelativeRotation(FRotator(0, -90,0 ).Quaternion());
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) {
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ASA_RangedWeapon::SetFire);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ASA_RangedWeapon::ReleaseFire);

		}
	}
}

