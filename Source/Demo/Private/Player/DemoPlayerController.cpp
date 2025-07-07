#include "Player/DemoPlayerController.h"
#include "Player/DemoPlayerState.h"
#include "AbilitySystemComponent.h"

void ADemoPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ADemoPlayerState* PS = GetPlayerState<ADemoPlayerState>();

    if (PS)
    {
        PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);

    }
}

// TODO - Add HUD stuff
