// Mostafa Eldesouky


#include "AbilitySystem/Attribute/AuraAttributes.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Interfaces/AttributeInterface.h"
#include "Interfaces/Combat.h"
#include "Net/UnrealNetwork.h"
#include "Statics/AuraFunctionLibrary.h"

UAuraAttributes::UAuraAttributes()
{
	FuncPtrs.Add(GetHealthAttribute);
	FuncPtrs.Add(GetMaxHealthAttribute);
	FuncPtrs.Add(GetManaAttribute);
	FuncPtrs.Add(GetMaxManaAttribute);
	FuncPtrs.Add(GetStrengthAttribute);
	FuncPtrs.Add(GetResilienceAttribute);
	FuncPtrs.Add(GetIntelligenceAttribute);
	FuncPtrs.Add(GetAttackRangeAttribute);
	FuncPtrs.Add(GetAttackSpeedAttribute);
	FuncPtrs.Add(GetCriticalDamageAttribute);
	FuncPtrs.Add(GetPhysicalArmorAttribute);
	FuncPtrs.Add(GetMagicalArmorAttribute);
	FuncPtrs.Add(GetMovementSpeedAttribute);
	FuncPtrs.Add(GetCooldownReductionAttribute);
	FuncPtrs.Add(GetLifeStealAttribute);
	FuncPtrs.Add(GetPhysicalPenetrationAttribute);
	FuncPtrs.Add(GetMagicalPenetrationAttribute);
	FuncPtrs.Add(GetHealthRegenAttribute);
	FuncPtrs.Add(GetManaRegenAttribute);
	FuncPtrs.Add(GetDamageBlockAttribute);
}
void UAuraAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, AttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, CriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, PhysicalArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MagicalArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, LifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, PhysicalPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MagicalPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, DamageBlock, COND_None, REPNOTIFY_Always);
}
void UAuraAttributes::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, MaxHealth, OldValue);
}
void UAuraAttributes::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Health, OldValue);
}
void UAuraAttributes::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, MaxMana, OldValue);
}
void UAuraAttributes::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Mana, OldValue);
}
void UAuraAttributes::OnRep_Strength(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Strength, OldValue);
}
void UAuraAttributes::OnRep_Resilience(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Resilience, OldValue);
}
void UAuraAttributes::OnRep_Intelligence(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Intelligence, OldValue);
}
void UAuraAttributes::OnRep_AttackRange(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, AttackRange, OldValue);
}
void UAuraAttributes::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, AttackSpeed, OldValue);
}
void UAuraAttributes::OnRep_CriticalDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, CriticalDamage, OldValue);
}
void UAuraAttributes::OnRep_PhysicalArmor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, PhysicalArmor, OldValue);
}
void UAuraAttributes::OnRep_MagicalArmor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, MagicalArmor, OldValue);
}
void UAuraAttributes::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, MovementSpeed, OldValue);
}
void UAuraAttributes::OnRep_CooldownReduction(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, CooldownReduction, OldValue);
}
void UAuraAttributes::OnRep_LifeSteal(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, LifeSteal, OldValue);
}
void UAuraAttributes::OnRep_PhysicalPenetration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, PhysicalPenetration, OldValue);
}
void UAuraAttributes::OnRep_MagicalPenetration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, MagicalPenetration, OldValue);
}
void UAuraAttributes::OnRep_HealthRegen(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, HealthRegen, OldValue);
}
void UAuraAttributes::OnRep_ManaRegen(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, ManaRegen, OldValue);
}
void UAuraAttributes::OnRep_DamageBlock(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, DamageBlock, OldValue);
}
void UAuraAttributes::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	ClampAttributes(Data);
}
void UAuraAttributes::ClampAttributes(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetInComingPhysicalDamageAttribute() || Data.EvaluatedData.Attribute == GetInComingMagicalDamageAttribute())
		ComplexDamageCalc(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if (GetHealth() <= 0.f)
			Cast<ICombat>(GetOwningAbilitySystemComponent()->GetAvatarActor())->GetOnDeathDelegate().Broadcast();
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	
	if (Data.EvaluatedData.Attribute == GetCooldownReductionAttribute())
		SetCooldownReduction(FMath::Clamp(GetCooldownReduction(), 0.f, 80.f));
	
	if (Data.EvaluatedData.Attribute == GetLifeStealAttribute())
		SetLifeSteal(FMath::Clamp(GetLifeSteal(), 0.f, 100.f));
	
	if (Data.EvaluatedData.Attribute == GetAttackSpeedAttribute())
		SetAttackSpeed(FMath::Max(GetAttackSpeed(), 0.1f));
	
	if (Data.EvaluatedData.Attribute == GetAttackRangeAttribute())
		SetAttackRange(FMath::Max(GetAttackRange(), 0.f));
}
void UAuraAttributes::ComplexDamageCalc(const struct FGameplayEffectModCallbackData& Data) 
{
	auto SrcAttribute = Cast<IAttributeInterface>(Data.EffectSpec.GetEffectContext().Get()->GetInstigatorAbilitySystemComponent()->GetAvatarActor())->GetAuraAttributes();
	auto SrcCriticalDamage = SrcAttribute->GetCriticalDamage();
	auto TargetDamageBlock = GetDamageBlock();
	float IncomingDamage = Data.EvaluatedData.Magnitude;
	float health = GetHealth();
	if (FMath::RandRange(1,100) <= 25)
	{
		IncomingDamage += SrcCriticalDamage;
		// bind to deleget to set floating text color red
	}
	if (FMath::RandRange(1,100) <= 25)
	{
		IncomingDamage -= TargetDamageBlock;
		// bind to deleget to set floating text color green
	}
	if (Data.EvaluatedData.Attribute.GetName() == GetInComingPhysicalDamageAttribute().GetName())
	{
		SetInComingPhysicalDamage(0.f);
		auto SrcPhysicalPenetration = SrcAttribute->GetPhysicalPenetration();
		auto TargetPhysicalArmor = GetPhysicalArmor();
		TargetPhysicalArmor -= SrcPhysicalPenetration;
		IncomingDamage -= TargetPhysicalArmor;
	}
	else if (Data.EvaluatedData.Attribute.GetName() == GetInComingMagicalDamageAttribute().GetName())
	{
		SetInComingMagicalDamage(0.f);
		auto SrcMagicalPenetration = SrcAttribute->GetMagicalPenetration();
		auto TargetMagicalArmor = GetMagicalArmor();
		TargetMagicalArmor -= SrcMagicalPenetration;
		IncomingDamage -= TargetMagicalArmor;
	}
	health -= IncomingDamage;
	SetHealth(FMath::Clamp(health, 0.f, GetMaxHealth()));
	if (GetHealth() <= 0.f)
		Cast<ICombat>(GetOwningAbilitySystemComponent()->GetAvatarActor())->GetOnDeathDelegate().Broadcast(); 
	// bind to deleget to set floating text color white  
}
