// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SA_HUD.generated.h"

class UImage;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class SHOOTERACECOM_API USA_HUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(meta = (BindWidget))
	UImage* CrossHair;
};
