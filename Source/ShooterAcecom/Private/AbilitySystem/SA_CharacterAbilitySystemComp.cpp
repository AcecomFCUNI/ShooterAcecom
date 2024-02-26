// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SA_CharacterAbilitySystemComp.h"

void USA_CharacterAbilitySystemComp::ReceiveDamage(USA_CharacterAbilitySystemComp* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
