// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Highlights.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UHighlights : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UFUNCTION()
	void OnRMBPressed(FGameplayEventData Payload);
	void TraceUnderMouse();
	TScriptInterface<ICombat> CurrentTarget{nullptr};
	TScriptInterface<ICombat> LastTarget{nullptr};
};

