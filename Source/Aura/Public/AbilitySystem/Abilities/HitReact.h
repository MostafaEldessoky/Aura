// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HitReact.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UHitReact : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual  void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	TScriptInterface<ICombat> CombatCharacter;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag PlayedMontageTag;
	UFUNCTION()
	void OnHitReactMontageBlendOut();
};
