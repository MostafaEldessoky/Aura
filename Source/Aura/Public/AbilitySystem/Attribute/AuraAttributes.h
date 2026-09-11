// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributes : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributes();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	TArray<FGameplayAttribute(*)()> FuncPtrs;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	UPROPERTY(ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	UPROPERTY(ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	UPROPERTY(ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	UPROPERTY(ReplicatedUsing = OnRep_PhysicalDamage)
	FGameplayAttributeData PhysicalDamage;
	UPROPERTY(ReplicatedUsing = OnRep_MagicalDamage)
	FGameplayAttributeData MagicalDamage;
	UPROPERTY(ReplicatedUsing = OnRep_AttackRange)
	FGameplayAttributeData AttackRange;
	UPROPERTY(ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	UPROPERTY(ReplicatedUsing = OnRep_CriticalChance)
	FGameplayAttributeData CriticalChance;
	UPROPERTY(ReplicatedUsing = OnRep_CriticalDamage)
	FGameplayAttributeData CriticalDamage;
	UPROPERTY(ReplicatedUsing = OnRep_PhysicalArmor)
	FGameplayAttributeData PhysicalArmor;
	UPROPERTY(ReplicatedUsing = OnRep_MagicalArmor)
	FGameplayAttributeData MagicalArmor;
	UPROPERTY(ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	UPROPERTY(ReplicatedUsing = OnRep_CooldownReduction)
	FGameplayAttributeData CooldownReduction;
	UPROPERTY(ReplicatedUsing = OnRep_LifeSteal)
	FGameplayAttributeData LifeSteal;
	UPROPERTY(ReplicatedUsing = OnRep_PhysicalPenetration)
	FGameplayAttributeData PhysicalPenetration;
	UPROPERTY(ReplicatedUsing = OnRep_MagicalPenetration)
	FGameplayAttributeData MagicalPenetration;
	UPROPERTY(ReplicatedUsing = OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;
	UPROPERTY(ReplicatedUsing = OnRep_ManaRegen)
	FGameplayAttributeData ManaRegen;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MagicalDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_AttackRange(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_PhysicalArmor(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MagicalArmor(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_CooldownReduction(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_LifeSteal(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_PhysicalPenetration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MagicalPenetration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldValue) const;

	ATTRIBUTE_ACCESSORS(UAuraAttributes, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MaxMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Mana);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Resilience);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, PhysicalDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MagicalDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, AttackRange);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, CriticalChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, CriticalDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, PhysicalArmor);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MagicalArmor);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MovementSpeed);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, CooldownReduction);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, LifeSteal);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, PhysicalPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MagicalPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, HealthRegen);
	ATTRIBUTE_ACCESSORS(UAuraAttributes, ManaRegen);

private:
	void ClampAttributes(const struct FGameplayEffectModCallbackData& Data);
	void PackageData(const struct FGameplayEffectModCallbackData& Data);
};



