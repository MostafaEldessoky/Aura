// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "AuraPlayer.generated.h"

class UAttributeSet;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraPlayer : public ACharacterBase
{
	GENERATED_BODY()
public:
	AAuraPlayer();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
private:
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	UCameraComponent* CameraComponent;
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	UAuraAttributes* AuraAttributes;
};
