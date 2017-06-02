// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityFramework.h"
#include "../GAGameEffect.h"
#include "../../GAAbilitiesComponent.h"
#include "AFPeriodApplicationAdd.h"


bool UAFPeriodApplicationAdd::ApplyEffect(const FGAEffectHandle& InHandle, struct FGAEffect* EffectIn,
	FGAEffectProperty& InProperty, struct FGAEffectContainer* InContainer)
{
	FTimerManager& DurationTimer = InHandle.GetContext().TargetComp->GetWorld()->GetTimerManager();

	FTimerDelegate delDuration = FTimerDelegate::CreateUObject(InHandle.GetContext().TargetComp.Get(), &UGAAbilitiesComponent::ExpireEffect, InHandle, InProperty);
	DurationTimer.SetTimer(InHandle.GetEffectPtr()->DurationTimerHandle, delDuration,
		InProperty.Duration, false);

	FTimerManager& PeriodTimer = InHandle.GetContext().TargetComp->GetWorld()->GetTimerManager();

	FTimerDelegate PeriodDuration = FTimerDelegate::CreateUObject(InHandle.GetContext().TargetComp.Get(), &UGAAbilitiesComponent::ExecuteEffect, InHandle, InProperty);
	PeriodTimer.SetTimer(InHandle.GetEffectPtr()->PeriodTimerHandle, PeriodDuration,
		InProperty.Period, true);

	InContainer->AddEffect(InHandle);
	//EffectIn.Context.TargetComp->ExecuteEffect(InHandle, InProperty);
	return true;
}

