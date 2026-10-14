// Mostafa Eldesouky


#include "AbilitySystem/Abilities/FireBlast.h"
#include "AbilitySystem/Tasks/AbilityTask_SendTargetDataToServer.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraFunctionLibrary.h"

void UFireBlast::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle,ActorInfo,ActivationInfo);
	CombatInterface = GetAvatarActorFromActorInfo();
	for (const auto& temp : UAuraFunctionLibrary::GetBoundedVectors(CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),
	CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),
	CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),GetAbilityLevel()*2))
		UAuraFunctionLibrary::SpawnProjectile(GetAvatarActorFromActorInfo(),nullptr,temp,ProjectileID,1.8f,
		false,true,GetAssetTags().First(),GetAbilityLevel());
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}
