// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MeleeAttack.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UMeleeAttack : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void TraceUnderMouse(FGameplayEventData Payload);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UFUNCTION()
	void OnGameplayEventReceivedFromAnimNotify( FGameplayEventData Payload);
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag CueTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag DamageEffectTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag PlayedMontageTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag AnimNotifyTag;
};
