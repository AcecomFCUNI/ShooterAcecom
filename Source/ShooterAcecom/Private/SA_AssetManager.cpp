// Fill out your copyright notice in the Description page of Project Settings.


#include "SA_AssetManager.h"
#include "AbilitySystemGlobals.h"

void USA_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
