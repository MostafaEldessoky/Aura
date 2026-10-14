// Mostafa Eldesouky


#include "AbilitySystem/Attribute/AuraAttributes.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Interfaces/AttributeInterface.h"
#include "Interfaces/Combat.h"
#include "Net/UnrealNetwork.h"


UAuraAttributes::UAuraAttributes()
{
	FuncPointers.Add(GetLevelAttribute);
	FuncPointers.Add(GetMaxXPAttribute);
	FuncPointers.Add(GetXPAttribute);
	FuncPointers.Add(GetHealthAttribute);
	FuncPointers.Add(GetMaxHealthAttribute);
	FuncPointers.Add(GetManaAttribute);
	FuncPointers.Add(GetMaxManaAttribute);
	FuncPointers.Add(GetStrengthAttribute);
	FuncPointers.Add(GetAgilityAttribute);
	FuncPointers.Add(GetIntelligenceAttribute);
	FuncPointers.Add(GetAttackRangeAttribute);
	FuncPointers.Add(GetCriticalChanceAttribute);
	FuncPointers.Add(GetPhysicalArmorAttribute);
	FuncPointers.Add(GetMagicalArmorAttribute);
	FuncPointers.Add(GetMovementSpeedAttribute);
	FuncPointers.Add(GetCostReductionAttribute);
	FuncPointers.Add(GetCooldownReductionAttribute);
	FuncPointers.Add(GetLifeStealAttribute);
	FuncPointers.Add(GetPhysicalPenetrationAttribute);
	FuncPointers.Add(GetMagicalPenetrationAttribute);
}
void UAuraAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MaxXP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, XP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, AttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, PhysicalArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MagicalArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, CostReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, LifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, PhysicalPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributes, MagicalPenetration, COND_None, REPNOTIFY_Always);
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
void UAuraAttributes::OnRep_Agility(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Agility, OldValue);
}
void UAuraAttributes::OnRep_Intelligence(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Intelligence, OldValue);
}
void UAuraAttributes::OnRep_AttackRange(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, AttackRange, OldValue);
}
void UAuraAttributes::OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, CriticalChance, OldValue);
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
void UAuraAttributes::OnRep_CostReduction(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, CostReduction, OldValue);
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
void UAuraAttributes::OnRep_Level(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, Level, OldValue);
}
void UAuraAttributes::OnRep_MaxXP(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, MaxXP, OldValue);
}
void UAuraAttributes::OnRep_XP(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributes, XP, OldValue);
}
void UAuraAttributes::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	ClampAttributes(Data);
}
void UAuraAttributes::ClampAttributes(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if (GetHealth() <= 0.f)
			Cast<ICombat>(GetOwningAbilitySystemComponent()->GetAvatarActor())->GetOnDeathDelegate().Broadcast(Data.EffectSpec.GetEffectContext().GetInstigator());
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
}
