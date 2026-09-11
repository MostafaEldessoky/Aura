// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PrimaryMoveAttack.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UPrimaryMoveAttack : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPrimaryMoveAttack();
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
