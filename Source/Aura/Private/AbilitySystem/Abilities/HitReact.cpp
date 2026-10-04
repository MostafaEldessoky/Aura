// Mostafa Eldesouky


#include "AbilitySystem/Abilities/HitReact.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Data/AuraData.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraSubSystem.h"


void UHitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CombatCharacter = GetAvatarActorFromActorInfo();
	auto PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,FName(),
		UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].Montages[PlayedMontageTag]);
	PlayMontageAndWait->OnBlendOut.AddDynamic(this,&UHitReact::OnHitReactMontageBlendOut);
	PlayMontageAndWait->ReadyForActivation();
}

void UHitReact::OnHitReactMontageBlendOut()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}
