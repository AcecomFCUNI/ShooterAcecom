// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShooterAcecom/ShooterAcecom.h"
#include "SA_CharacterGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API USA_CharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	USA_CharacterGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	SA_AbilityID AbilityID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	int32 AbilityInputID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};
