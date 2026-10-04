// Mostafa Eldesouky


#include "AbilitySystem/Abilities/MeleeAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "AbilitySystem/Tasks/AbilityTask_CanAttack.h"
#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraFunctionLibrary.h"


void UMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		auto temp = UAbilityTask_CanAttack::GetCanAttack(this,HitResult);
		temp->OnCanAttack.AddLambda([this,HitResult]()
		{
			UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),HitResult.GetActor()->GetActorLocation(),
				PlayedMontageTag,AnimNotifyTag,STATIC_FUNCTION_FNAME(TEXT("UMeleeAttack::OnGameplayEventReceivedFromAnimNotify")));
		});
		temp->ReadyForActivation();
	});
	TargetDataTask->ReadyForActivation();
}
void UMeleeAttack::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	FGameplayCueParameters Params;
		Params.Location = Cast<ICombat>(GetAvatarActorFromActorInfo())->GetWeaponMechanicSocketTransform().GetLocation();
	if (GetCurrentActorInfo()->IsNetAuthority())
	{
		UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(GetAvatarActorFromActorInfo(),CueTag,Params);
		UAuraFunctionLibrary::ApplyRadialDamageEffect(
		GetAvatarActorFromActorInfo(),
		TArray{GetAvatarActorFromActorInfo()},
		Cast<ICombat>(GetAvatarActorFromActorInfo())->GetWeaponMechanicSocketTransform().GetLocation(),
		50.f,DamageEffectTag,GetAbilityLevel());
	}
	else
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),CueTag,Params);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}
