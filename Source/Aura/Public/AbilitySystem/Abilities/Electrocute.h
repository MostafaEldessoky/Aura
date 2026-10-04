// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Electrocute.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UElectrocute : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	bool bInputReleased{false};
	bool bCueActivated{false};
	FHitResult Target;
	FTimerHandle ElectrocuteTimerHandle;
	void OnApplyingElectrocute();
	UFUNCTION()
	void OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload);
	UFUNCTION()
	void OnInputReleased(float TimeHeld);
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	float ElectrocuteSearchRadius{500.f};
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	int32 NumberOfTargets{1};
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag InputReleasedTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag PlayedMontageTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag AnimNotifyTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag CueTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag DamageEffectTag;
};
