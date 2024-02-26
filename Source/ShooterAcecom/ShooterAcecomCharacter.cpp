// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterAcecomCharacter.h"
#include "ShooterAcecomProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/SA_CharacterAbilitySystemComp.h"
#include "AbilitySystem/SA_CharacterGameplayAbility.h"
#include "AbilitySystem/SA_CharacterAttributeSet.h"


//////////////////////////////////////////////////////////////////////////
// AShooterAcecomCharacter

AShooterAcecomCharacter::AShooterAcecomCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
		
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(10.f, 0.f, 80.f)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	// Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	// Mesh1P->SetOnlyOwnerSee(true);
	// Mesh1P->SetupAttachment(CameraComponent);
	// Mesh1P->bCastDynamicShadow = false;
	// Mesh1P->CastShadow = false;
	// //Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	// Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));

}

void AShooterAcecomCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AShooterAcecomCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterAcecomCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterAcecomCharacter::Look);
	}
}


void AShooterAcecomCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AShooterAcecomCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AShooterAcecomCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AShooterAcecomCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AShooterAcecomCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven) {
		return;
	}
	for (TSubclassOf<USA_CharacterGameplayAbility>& StartupAbility : CharacterAbilities) {
		GrantAbility(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID));
	}
	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void AShooterAcecomCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid()) {
		return;
	}
	if (!DefaultAttributes) {
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (!NewHandle.IsValid()) {
		return;
	}
	FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());

}

void AShooterAcecomCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectsApplied) {
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : StartupEffects) {
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (!NewHandle.IsValid()) {
			continue;
		}
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
	AbilitySystemComponent->StartupEffectsApplied = true;
}

void AShooterAcecomCharacter::SetHealth(float Health)
{
	if (AttributeSet.IsValid()) {
		AttributeSet->SetHealth(Health);
	}
}

void AShooterAcecomCharacter::SetMaxHealth(float MaxHealth)
{
	if (AttributeSet.IsValid()) {
		AttributeSet->SetMaxHealth(MaxHealth);
	}
}

void AShooterAcecomCharacter::GrantAbility(TSubclassOf<USA_CharacterGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || IsValid(AbilityClass))
	{
		return;
	}
	USA_CharacterGameplayAbility* Ability = AbilityClass->GetDefaultObject<USA_CharacterGameplayAbility>();
	if (IsValid(Ability))
	{
		FGameplayAbilitySpec AbilitySpec(
			Ability,
			Level,
			InputCode
		);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void AShooterAcecomCharacter::ActivateAbility(int32 InputCode)
{
	if (IsValid(AbilitySystemComponent.Get()))
	{
		AbilitySystemComponent->AbilityLocalInputPressed(InputCode);
	}
}

UAbilitySystemComponent* AShooterAcecomCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent.Get();
}

bool AShooterAcecomCharacter::IsAlive() const {
	return GetHealth() > .0f;
}

int32 AShooterAcecomCharacter::GetAbilityLevel(SA_AbilityID AbilityId) const
{
	return 1;
}

void AShooterAcecomCharacter::RemoveCharacterAbilities() const
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven) {
		return;
	}
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities()) {
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass())) {
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++) {
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

void AShooterAcecomCharacter::Die()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid()) {
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectsTagsToRemove;
		EffectsTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsTagsToRemove = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage) {
		PlayAnimMontage(DeathMontage);
	}
	else {
		FinishDying();
	}
}

void AShooterAcecomCharacter::FinishDying()
{
	Destroy();
}

float AShooterAcecomCharacter::GetCharacterLevel() const
{
	if (AttributeSet.IsValid()) {
		return AttributeSet->GetLevel();
	}
	return 0.0f;
}

float AShooterAcecomCharacter::GetHealth() const
{
	if (AttributeSet.IsValid()) {
		return AttributeSet->GetHealth();
	}
	return 0.0f;
}

float AShooterAcecomCharacter::GetMaxHealth() const
{
	if (AttributeSet.IsValid()) {
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}
