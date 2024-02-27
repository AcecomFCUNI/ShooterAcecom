// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SA_PlayerState.h"
#include "AbilitySystem/SA_CharacterAttributeSet.h"
#include "AbilitySystem/SA_CharacterAbilitySystemComp.h" 	


ASA_PlayerState::ASA_PlayerState() {
	AbilitySystemComponent = CreateDefaultSubobject<USA_CharacterAbilitySystemComp>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USA_CharacterAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ASA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USA_CharacterAttributeSet* ASA_PlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

bool ASA_PlayerState::IsAlive() const
{
	return GetHealth() > .0f;
}

void ASA_PlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
}

float ASA_PlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ASA_PlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

int32 ASA_PlayerState::GetCharacterLevel() const
{
	return AttributeSet->GetLevel();
}

void ASA_PlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (!AbilitySystemComponent) {
		return;
	}
	HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ASA_PlayerState::HealthChanged);
	MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ASA_PlayerState::MaxHealthChanged);
	CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetLevelAttribute()).AddUObject(this, &ASA_PlayerState::CharacterLevelChanged);

	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ASA_PlayerState::StunTagChanged);
	
}

void ASA_PlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"));
}

void ASA_PlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"));
}


void ASA_PlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Level Changed!"));
}

void ASA_PlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0) {
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
