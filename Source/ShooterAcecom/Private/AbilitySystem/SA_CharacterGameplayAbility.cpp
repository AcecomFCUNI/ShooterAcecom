// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SA_CharacterGameplayAbility.h"
#include "AbilitySystem/SA_CharacterAbilitySystemComp.h"

USA_CharacterGameplayAbility::USA_CharacterGameplayAbility() 
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Block")));
}

void USA_CharacterGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if (ActivateAbilityOnGranted) {
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
