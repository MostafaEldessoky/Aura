// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TraceUnderMouse.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UTraceUnderMouse : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	void TraceUnderMouse();

};
