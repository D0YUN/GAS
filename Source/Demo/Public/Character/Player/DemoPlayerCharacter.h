#pragma once

#include "CoreMinimal.h"
#include "Character/DemoCharacterBase.h"
#include "Player/DemoPlayerState.h"
#include "DemoPlayerCharacter.generated.h"

UCLASS()
class DEMO_API ADemoPlayerCharacter : public ADemoCharacterBase
{
	GENERATED_BODY()
	
public:
	ADemoPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	class USpringArmComponent* GetCameraBoom();

	class UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable, Category = "Demo|Camera")
	float GetStartingCameraBoomLength();

	UFUNCTION(BlueprintCallable, Category = "Demo|Camera")
	FVector GetStartingCameraBoomLocation();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Demo|Camera")
	float BaseTurnRate = 45.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Demo|Camera")
	float BaseLookUpRate = 45.f;

	UPROPERTY(BlueprintReadOnly, Category = "Demo|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, Category = "Demo|Camera")
	FVector StartingCameraBoomLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Demo|Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Demo|Camera")
	class UCameraComponent* FollowCamera;

	bool ASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	void LookUp(float Value);

	void LookUpRate(float Value);

	void Turn(float Value);

	void TurnRate(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;

	void InitializeStartingValues(ADemoPlayerState* PS);

	void BindASCInput();
};
