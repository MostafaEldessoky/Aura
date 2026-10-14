// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FireBlast.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UFireBlast : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ProjectileID;
	TScriptInterface<ICombat> CombatInterface;
};
