// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Cooldown.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UCooldown : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UCooldown();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	FGameplayEffectAttributeCaptureDefinition CooldownReductionDef;
};
