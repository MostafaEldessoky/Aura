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
	
	TArray<FGameplayAttribute(*)()> FuncPointers;
	
	UPROPERTY(ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Level);
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxXP)
	FGameplayAttributeData MaxXP;
	UFUNCTION()
	void OnRep_MaxXP(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MaxXP);
	
	UPROPERTY(ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;
	UFUNCTION()
	void OnRep_XP(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, XP);
	
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Health);
	
	UPROPERTY(ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Mana);
	
	UPROPERTY(ReplicatedUsing = OnRep_AttackRange)
	FGameplayAttributeData AttackRange;
	UFUNCTION()
	void OnRep_AttackRange(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, AttackRange);
	
	UPROPERTY(ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MovementSpeed);
	
	UPROPERTY(ReplicatedUsing = OnRep_CostReduction)
	FGameplayAttributeData CostReduction;
	UFUNCTION()
	void OnRep_CostReduction(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, CostReduction);
	
	UPROPERTY(ReplicatedUsing = OnRep_CooldownReduction)
	FGameplayAttributeData CooldownReduction;
	UFUNCTION()
	void OnRep_CooldownReduction(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, CooldownReduction);
	
	UPROPERTY(ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Strength);
	
	UPROPERTY(ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Agility);
	
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, Intelligence);
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MaxHealth);
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MaxMana);
	
	UPROPERTY(ReplicatedUsing = OnRep_CriticalChance)
	FGameplayAttributeData CriticalChance;
	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, CriticalChance);
	
	UPROPERTY(ReplicatedUsing = OnRep_LifeSteal)
	FGameplayAttributeData LifeSteal;
	UFUNCTION()
	void OnRep_LifeSteal(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, LifeSteal);
	
	UPROPERTY(ReplicatedUsing = OnRep_PhysicalPenetration)
	FGameplayAttributeData PhysicalPenetration;
	UFUNCTION()
	void OnRep_PhysicalPenetration(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, PhysicalPenetration);
	
	UPROPERTY(ReplicatedUsing = OnRep_MagicalPenetration)
	FGameplayAttributeData MagicalPenetration;
	UFUNCTION()
	void OnRep_MagicalPenetration(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MagicalPenetration);
	
	UPROPERTY(ReplicatedUsing = OnRep_PhysicalArmor)
	FGameplayAttributeData PhysicalArmor;
	UFUNCTION()
	void OnRep_PhysicalArmor(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, PhysicalArmor);
	
	UPROPERTY(ReplicatedUsing = OnRep_MagicalArmor)
	FGameplayAttributeData MagicalArmor;
	UFUNCTION()
	void OnRep_MagicalArmor(const FGameplayAttributeData& OldValue) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributes, MagicalArmor);

private:
	void ClampAttributes(const struct FGameplayEffectModCallbackData& Data);
};