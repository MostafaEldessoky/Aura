// Mostafa Eldesouky


#include "AbilitySystem/Custom Calc/Cost.h"

#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"

UCost::UCost()
{
	CostReductionDef.AttributeToCapture = UAuraAttributes::GetCostReductionAttribute();
	CostReductionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CostReductionDef.bSnapshot = true;
	
	RelevantAttributesToCapture.Add(CostReductionDef);
}

float UCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters Params;
	Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float CostReduction = 0.f;
	GetCapturedAttributeMagnitude(CostReductionDef,Spec,Params,CostReduction);
	return -1 * UAuraSubSystem::GetAuraSubSystem(Spec.GetEffectContext().Get()->GetInstigator())->AuraData->AbilitiesClasses[Spec.GetContext().GetAbility()->GetAssetTags().First()].Cost.GetValueAtLevel(Spec.GetContext().GetAbility()->GetAbilityLevel()) * CostReduction;
}
