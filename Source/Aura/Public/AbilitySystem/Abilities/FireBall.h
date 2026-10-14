// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FireBall.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UFireBall : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void TraceUnderMouse(FGameplayEventData Payload);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION()
	virtual void OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload);
	FHitResult Target;
private:
	bool bOneTrace{false};
	TScriptInterface<ICombat> CombatInterface;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	bool bHoming{false};
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag ProjectileID;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag PlayedMontageTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag AnimNotifyTag;
};
