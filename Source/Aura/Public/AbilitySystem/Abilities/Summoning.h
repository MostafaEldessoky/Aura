// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Summoning.generated.h"

class AAuraEnemyBase;
class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API USummoning : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void TraceUnderMouse(FGameplayEventData Payload);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag PlayedMontageTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag AnimNotifyTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	TArray<TSubclassOf<AAuraEnemyBase>> EnemyClasses;
	UFUNCTION()
	virtual void OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload);
};
