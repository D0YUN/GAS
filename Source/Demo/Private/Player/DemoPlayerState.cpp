#include "Player/DemoPlayerState.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"


ADemoPlayerState::ADemoPlayerState()
{
    AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

    NetUpdateFrequency = 100.f;
    DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

class UAbilitySystemComponent* ADemoPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

class UCharacterAttributeSetBase* ADemoPlayerState::GetAttributeSetBase() const
{
    return AttributeSetBase;
}

bool ADemoPlayerState::IsAlive() const
{
    return GetHealth() > 0.f;
}

void ADemoPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
    // HUD implement �Ŀ� ����
}

float ADemoPlayerState::GetHealth() const
{
    return AttributeSetBase->GetHealth();
}

float ADemoPlayerState::GetMaxHealth() const
{
    return AttributeSetBase->GetMaxHealth();
}

float ADemoPlayerState::GetMana() const
{
    return AttributeSetBase->GetMana();
}

float ADemoPlayerState::GetMaxMana() const
{
    return AttributeSetBase->GetMaxMana();
}

int32 ADemoPlayerState::GetCharacterLevel() const
{
    return AttributeSetBase->GetLevel();
}

void ADemoPlayerState::BeginPlay()
{
    Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ADemoPlayerState::HealthChanged);
        MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &ADemoPlayerState::MaxHealthChanged);
        ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &ADemoPlayerState::ManaChanged);
        MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &ADemoPlayerState::MaxManaChanged);
        CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &ADemoPlayerState::CharacterLevelChanged);

        AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ADemoPlayerState::StunTagChanged);
    }
}

void ADemoPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
    UE_LOG(LogTemp, Warning, TEXT("Health Changed!"));
}

void ADemoPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
    UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"));
}

void ADemoPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
    UE_LOG(LogTemp, Warning, TEXT("Mana Changed!"));
}

void ADemoPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
    UE_LOG(LogTemp, Warning, TEXT("Max Mana Changed!"));
}

void ADemoPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
    UE_LOG(LogTemp, Warning, TEXT("Character Level Changed!"));
}

void ADemoPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
    if (NewCount > 0)
    {
        FGameplayTagContainer AbilityTagsToCancel;
        AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

        FGameplayTagContainer AbilityTagsToIgnore;
        AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

        AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
    }
}
