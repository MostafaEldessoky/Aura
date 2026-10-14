// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageSystem.generated.h"



/**
 * 
 */
UCLASS()
class AURA_API UDamageSystem : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UDamageSystem();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
private:
	FGameplayEffectAttributeCaptureDefinition CriticalChanceDef;
	FGameplayEffectAttributeCaptureDefinition LifeStealDef;
	FGameplayEffectAttributeCaptureDefinition PhysicalPenetrationDef;
	FGameplayEffectAttributeCaptureDefinition PhysicalArmorDef;
	FGameplayEffectAttributeCaptureDefinition MagicalPenetrationDef;
	FGameplayEffectAttributeCaptureDefinition MagicalArmorDef;
};
