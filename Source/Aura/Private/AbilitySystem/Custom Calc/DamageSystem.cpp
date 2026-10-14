// Mostafa Eldesouky


#include "AbilitySystem/Custom Calc/DamageSystem.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Statics/AuraSubSystem.h"

UDamageSystem::UDamageSystem()
{
	CriticalChanceDef.AttributeToCapture = UAuraAttributes::GetCriticalChanceAttribute();
	CriticalChanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	CriticalChanceDef.bSnapshot = true;
	RelevantAttributesToCapture.Add(CriticalChanceDef);
	
	LifeStealDef.AttributeToCapture = UAuraAttributes::GetLifeStealAttribute();
	LifeStealDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	LifeStealDef.bSnapshot = true;
	RelevantAttributesToCapture.Add(LifeStealDef);
	
	PhysicalPenetrationDef.AttributeToCapture = UAuraAttributes::GetPhysicalPenetrationAttribute();
	PhysicalPenetrationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	PhysicalPenetrationDef.bSnapshot = true;
	RelevantAttributesToCapture.Add(PhysicalPenetrationDef);
	
	PhysicalArmorDef.AttributeToCapture = UAuraAttributes::GetPhysicalArmorAttribute();
	PhysicalArmorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	PhysicalArmorDef.bSnapshot = true;
	RelevantAttributesToCapture.Add(PhysicalArmorDef);
	
	MagicalPenetrationDef.AttributeToCapture = UAuraAttributes::GetMagicalPenetrationAttribute();
	MagicalPenetrationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MagicalPenetrationDef.bSnapshot = true;
	RelevantAttributesToCapture.Add(MagicalPenetrationDef);
	
	MagicalArmorDef.AttributeToCapture = UAuraAttributes::GetMagicalArmorAttribute();
	MagicalArmorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MagicalArmorDef.bSnapshot = true;
	RelevantAttributesToCapture.Add(MagicalArmorDef);
	
}

void UDamageSystem::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                           FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	auto TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	auto SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	
	FAggregatorEvaluateParameters AggregatorParams;
	AggregatorParams.SourceTags = ExecutionParams.GetOwningSpec().CapturedSourceTags.GetAggregatedTags();
	AggregatorParams.TargetTags = ExecutionParams.GetOwningSpec().CapturedTargetTags.GetAggregatedTags();
	
	auto AbilityData = UAuraSubSystem::GetAuraSubSystem(SourceASC)->AuraData->AbilitiesClasses[ExecutionParams.GetOwningSpec().GetEffectContext().GetAbility()->GetAssetTags().First()];
	
	float Penetration = 0.f;
	float Armor = 0.f;
	switch (AbilityData.DamageType)
	{
		case EDamageType::Physical :
			if (AbilityData.PassiveTags.HasTagExact(Aura::Abilities::Passive::PhysicalPenetration)) 
				ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalPenetrationDef,AggregatorParams,Penetration);
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalArmorDef,AggregatorParams,Armor);
			break;
		case EDamageType::Magical :
			if (AbilityData.PassiveTags.HasTagExact(Aura::Abilities::Passive::MagicalPenetration)) 
				ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicalPenetrationDef,AggregatorParams,Penetration);
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicalArmorDef,AggregatorParams,Armor);
			break;
		default:
			return;
	}
	
	float CriticalChance = 0.f;
	if (AbilityData.PassiveTags.HasTagExact(Aura::Abilities::Passive::CriticalChance)) 
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CriticalChanceDef,AggregatorParams,CriticalChance);
	float LifeSteal = 0.f;
	if (AbilityData.PassiveTags.HasTagExact(Aura::Abilities::Passive::LifeSteal)) 
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(LifeStealDef,AggregatorParams,LifeSteal);
	
	float Damage = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(Aura::SetByCaller::Damage);
	
	if (FMath::RandRange(0.f,100.f) <= CriticalChance)
		Damage = Damage * 2.f;
	Damage += Penetration - Armor;
	
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAuraAttributes::GetHealthAttribute(),EGameplayModOp::AddBase,-Damage));
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetASC->GetAvatarActor(),Aura::Abilities::HitReact,FGameplayEventData());
	
	for(const auto& temp : AbilityData.BuffsToApply)
		if (FMath::RandRange(0.f,100.f) <= temp.Chance)
		{
			UGameplayEffect* BuffEffect = NewObject<UGameplayEffect>(GetTransientPackage());
			BuffEffect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
			BuffEffect->DurationMagnitude = FGameplayEffectModifierMagnitude(temp.Duration);
			BuffEffect->Period = temp.Period;
			FGameplayModifierInfo ModifierInfo;
			ModifierInfo.Attribute = temp.EffectedAttribute;
			ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(temp.Damage);
			ModifierInfo.ModifierOp = EGameplayModOp::AddBase;
			BuffEffect->Modifiers.Add(ModifierInfo);
			BuffEffect->CachedGrantedTags = temp.GrantedTag.GetSingleTagContainer();
			BuffEffect->GameplayCues.Add(temp.GameplayCues);
			FGameplayEffectSpec* BuffEffectSpec = new FGameplayEffectSpec(BuffEffect,SourceASC->MakeEffectContext(),1.f);
			SourceASC->ApplyGameplayEffectSpecToTarget(*BuffEffectSpec,TargetASC);
		}
	
	if (FMath::RandRange(0.f,100.f) <= LifeSteal)
	{
		UGameplayEffect* LifeStealEffect = NewObject<UGameplayEffect>(GetTransientPackage());
		LifeStealEffect->DurationPolicy = EGameplayEffectDurationType::Instant;
		FGameplayModifierInfo ModifierInfo;
		ModifierInfo.Attribute = UAuraAttributes::GetHealthAttribute();
		ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(Damage);
		ModifierInfo.ModifierOp = EGameplayModOp::AddBase;
		LifeStealEffect->Modifiers.Add(ModifierInfo);
		FGameplayEffectSpec* BuffEffectSpec = new FGameplayEffectSpec(LifeStealEffect,SourceASC->MakeEffectContext(),1.f);
		SourceASC->ApplyGameplayEffectSpecToSelf(*BuffEffectSpec);
	}
}
