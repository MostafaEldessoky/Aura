// Mostafa Eldesouky


#include "PlayerState/AuraState.h"
#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"

AAuraState::AAuraState()
{
	SetNetUpdateFrequency(100.f);
	SetReplicates(true);
	AuraASC = CreateDefaultSubobject<UAuraASC>(TEXT("AuraASC"));
	AuraAttributes = CreateDefaultSubobject<UAuraAttributes>(TEXT("AuraAttributes"));
}
UAbilitySystemComponent* AAuraState::GetAbilitySystemComponent() const
{
	return AuraASC.Get();
}
UAuraAttributes* AAuraState::GetAuraAttributes() const
{
	return AuraAttributes.Get();
}
