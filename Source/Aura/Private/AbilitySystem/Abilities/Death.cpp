// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Death.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "Components/CapsuleComponent.h"
#include "Data/AuraData.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraFunctionLibrary.h"
#include "Statics/AuraSubSystem.h"


void UDeath::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(GetAvatarActorFromActorInfo(),DeathBehaviorTag,FGameplayCueParameters());
	GetAvatarActorFromActorInfo()->SetLifeSpan(5.f);
	auto temp = const_cast<AActor*>(TriggerEventData->Target.Get());
	if (temp)
		UAuraFunctionLibrary::ApplyEffectToTarget(GetAvatarActorFromActorInfo(),temp,FVector(0,0,0),XPTag,GetAssetTags().First(),GetAbilityLevel());
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(GetAvatarActorFromActorInfo(),DissolveCueTag,FGameplayCueParameters());
	EndAbility(Handle,ActorInfo ,ActivationInfo,false,false);
}

