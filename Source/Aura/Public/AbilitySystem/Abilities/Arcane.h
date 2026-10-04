// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Arcane.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UArcane : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UPROPERTY()
	UDecalComponent* decal;
	FHitResult Target;
	UFUNCTION()
	void OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload);
	UFUNCTION()
	void OnInputReleased(float TimeHeld);
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	float RadiusOfActivation;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag InputReleasedTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag PlayedMontageTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag AnimNotifyTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag ArcaneCueTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag DamageEffectTag;
};
