// Mostafa Eldesouky


#include "AbilitySystem/Abilities/MeleeAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_CanAttack.h"
#include "AbilitySystem/Tasks/AbilityTask_SendTargetDataToServer.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraFunctionLibrary.h"


void UMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto WaitGameplayEventTraceUnderMouse = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Aura::Abilities::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->EventReceived.AddDynamic(this,&UMeleeAttack::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->ReadyForActivation();
}
void UMeleeAttack::TraceUnderMouse(FGameplayEventData Payload)
{
	auto TargetDataTask = UAbilityTask_SendTargetDataToServer::SendTargetDataToServer(this,Payload.TargetData);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FGameplayAbilityTargetDataHandle TargetData)
	{
		auto temp = UAbilityTask_CanAttack::GetCanAttack(this,*TargetData.Get(0)->GetHitResult());
		temp->OnCanAttack.AddLambda([this,TargetData]()
		{
			UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),TargetData.Get(0)->GetHitResult()->GetActor()->GetActorLocation(),
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
		50.f,DamageEffectTag,GetAssetTags().First(),GetAbilityLevel());
	}
	else
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),CueTag,Params);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}
