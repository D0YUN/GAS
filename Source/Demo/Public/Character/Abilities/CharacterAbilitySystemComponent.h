// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UCharacterAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

UCLASS()
class DEMO_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	// 데미지를 받은 곳 / 피해를 감소시키기 전 원래 데미지 / 방어력, 저항력, 피해 감소 버프 등을 반영한 실제 피해량
	virtual void ReceiveDamage(UCharacterAbilitySystemComponent* SoureASC, float UnmitigatedDamage, float MitigatedDamage);
};
