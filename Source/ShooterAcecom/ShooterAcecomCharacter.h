// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include <ShooterAcecom/ShooterAcecom.h>
#include "ShooterAcecomCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AShooterAcecomCharacter*, Character);

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class USA_CharacterGameplayAbility;

UCLASS(config=Game)
class AShooterAcecomCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	
public:
	AShooterAcecomCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "Shooter|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Character")
	virtual int32 GetAbilityLevel(SA_AbilityID AbilityId) const;

	virtual void RemoveCharacterAbilities() const;

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Shooter|Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category = "Shooter|Character|Attributes")
	float GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Character|Attributes")
	float GetMaxHealth() const;


protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter|Abilities")
	TWeakObjectPtr<class USA_CharacterAbilitySystemComp> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter|Abilities")
	TWeakObjectPtr<class USA_CharacterAttributeSet> AttributeSet;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shooter|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooter|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shooter|Abilities")
	TArray<TSubclassOf<USA_CharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shooter|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shooter|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);

	virtual void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "Shooter|Abilities")
	void GrantAbility(TSubclassOf<USA_CharacterGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

	UFUNCTION(BlueprintCallable, Category = "Shooter|Abilities")
	void ActivateAbility(int32 InputCode);

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


};

