// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActionWidget.h"
#include "MGActionWidget.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;

/**
 * An action widget that will get the icon of key that is currently assigned to the common input action on this widget
 * Replace MG with your project's acronym. I just chose MG for "My Game" as an example
 */
UCLASS(BlueprintType, Blueprintable)
class PAUSEMENU_API UMGActionWidget : public UCommonActionWidget
{
	GENERATED_BODY()

public:
	//~ Begin UCommonActionWidget interface
	virtual FSlateBrush GetIcon() const override;
	//~ End of UCommonActionWidget interface

private:
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
};
