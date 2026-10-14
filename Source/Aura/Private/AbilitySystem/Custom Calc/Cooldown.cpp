// Mostafa Eldesouky


#include "AbilitySystem/Custom Calc/Cooldown.h"

#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"

UCooldown::UCooldown()
{
	CooldownReductionDef.AttributeToCapture = UAuraAttributes::GetCooldownReductionAttribute();
	CooldownReductionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CooldownReductionDef.bSnapshot = true;
	
	RelevantAttributesToCapture.Add(CooldownReductionDef);
}

float UCooldown::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters Params;
	Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float CooldownReduction = 0.f;
	GetCapturedAttributeMagnitude(CooldownReductionDef,Spec,Params,CooldownReduction);
	return UAuraSubSystem::GetAuraSubSystem(Spec.GetEffectContext().Get()->GetInstigator())->AuraData->AbilitiesClasses[Spec.GetContext().GetAbility()->GetAssetTags().First()].Cooldown.GetValueAtLevel(Spec.GetContext().GetAbility()->GetAbilityLevel()) * CooldownReduction;
}
