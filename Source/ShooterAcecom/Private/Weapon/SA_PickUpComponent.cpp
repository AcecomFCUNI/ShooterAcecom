// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SA_PickUpComponent.h"

// Sets default values for this component's properties
USA_PickUpComponent::USA_PickUpComponent() {
	SphereRadius = 32.f;
}

// Called when the game starts
void USA_PickUpComponent::BeginPlay() {
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &USA_PickUpComponent::OnSphereBeginOverlap);
}

void USA_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	// Checking if it is a First Person Character overlapping
	AShooterAcecomCharacter* Character = Cast<AShooterAcecomCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}



