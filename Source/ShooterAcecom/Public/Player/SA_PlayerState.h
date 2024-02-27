// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "SA_PlayerState.generated.h"

class USA_CharacterAttributeSet;

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API ASA_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ASA_PlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	USA_CharacterAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	int32 GetCharacterLevel() const;

protected:
	UPROPERTY()
	class USA_CharacterAbilitySystemComp* AbilitySystemComponent;

	UPROPERTY()
	USA_CharacterAttributeSet* AttributeSet;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle CharacterLevelChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
