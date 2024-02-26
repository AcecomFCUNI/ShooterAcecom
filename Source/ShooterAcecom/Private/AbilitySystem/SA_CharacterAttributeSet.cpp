// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SA_CharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"

void USA_CharacterAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USA_CharacterAttributeSet, Level, OldLevel);
}

void USA_CharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USA_CharacterAttributeSet, Health, OldHealth);
}

void USA_CharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USA_CharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void USA_CharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(USA_CharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USA_CharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USA_CharacterAttributeSet, Level, COND_None, REPNOTIFY_Always);
}
