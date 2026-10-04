// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Characters/CharacterBase.h"
#include "AuraPlayer.generated.h"

class UAttributeSet;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraPlayer : public ACharacterBase, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AAuraPlayer();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual UDecalComponent* GetDecalComponent() override;
private:
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	UDecalComponent* DecalComponent;
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	UAuraAttributes* AuraAttributes;
};
