// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SA_CharacterAbilitySystemComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, USA_CharacterAbilitySystemComp*, SourceASC, float, UnmitigatedDamage, float, MitigateDamage);

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API USA_CharacterAbilitySystemComp : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(USA_CharacterAbilitySystemComp* SourceASC, float UnmitigatedDamage, float MitigatedDamage);


	
};
