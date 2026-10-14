// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Cost.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UCost();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	FGameplayEffectAttributeCaptureDefinition CostReductionDef;
};
