#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include <Demo/Demo.h>
#include "CharacterGameplayAbility.generated.h"


UCLASS()
class DEMO_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCharacterGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	DemoAbilityID AbilityInputID = DemoAbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	DemoAbilityID AbilityID = DemoAbilityID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivatedAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
