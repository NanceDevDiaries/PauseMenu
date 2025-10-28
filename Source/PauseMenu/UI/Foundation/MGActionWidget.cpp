// Fill out your copyright notice in the Description page of Project Settings.

#include "MGActionWidget.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"

FSlateBrush UMGActionWidget::GetIcon() const
{
	if (!IsDesignTime() && EnhancedInputAction && CommonUI::IsEnhancedInputSupportEnabled())
	{
		if (const UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem())
		{
			if (const UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = GetEnhancedInputSubsystem())
			{
				const TArray<FKey> BoundKeys = EnhancedInputSubsystem->QueryKeysMappedToAction(EnhancedInputAction);
				FSlateBrush SlateBrush;

				const ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();

				// This is where the code differs for Lyra's ULyraActionWidget, get brush set, not just brush at key 0
				bool IsUsingGamepadInput = CurrentInputType == ECommonInputType::Gamepad;
				const TArray<FKey> KeysRelatedToInputType = BoundKeys.FilterByPredicate(
					[IsUsingGamepadInput](const FKey& Key) { return Key.IsGamepadKey() == IsUsingGamepadInput; });

				if (!KeysRelatedToInputType.IsEmpty() && UCommonInputPlatformSettings::Get()->
					TryGetInputBrush(SlateBrush, KeysRelatedToInputType, CurrentInputType,
					                 CommonInputSubsystem->GetCurrentGamepadName()))
				{
					return SlateBrush;
				}
			}
		}
	}

	return Super::GetIcon();
}

UEnhancedInputLocalPlayerSubsystem* UMGActionWidget::GetEnhancedInputSubsystem() const
{
	const UWidget* BoundWidget = DisplayedBindingHandle.GetBoundWidget();
	if (const ULocalPlayer* BindingOwner = BoundWidget ? BoundWidget->GetOwningLocalPlayer() : GetOwningLocalPlayer())
	{
		return BindingOwner->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	}
	return nullptr;
}
