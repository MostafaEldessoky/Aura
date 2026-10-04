// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Arcane.h"
#include "AbilitySystemComponent.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "AbilitySystem/Tasks/AbilityTask_SendRandomPointsToServer.h"
#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "AbilitySystem/Tasks/AbilityTask_TraceUnderMouse.h"
#include "Components/DecalComponent.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraFunctionLibrary.h"


void UArcane::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto temp = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	temp->OnRelease.AddDynamic(this,&UArcane::OnInputReleased);
	temp->ReadyForActivation();
	if (GetCurrentActorInfo()->IsLocallyControlled())
	{
		GetCurrentActorInfo()->PlayerController->bShowMouseCursor = false;
		decal = Cast<ICombat>(GetAvatarActorFromActorInfo())->GetDecalComponent();
		decal->Activate();
		decal->SetVisibility(true);
	}
	auto TraceUnderMouseTask = UAbilityTask_TraceUnderMouse::TraceUnderMouse(this);
	TraceUnderMouseTask->OnTraceUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		if (decal && GetCurrentActorInfo()->IsLocallyControlled()) decal->SetWorldLocation(HitResult.ImpactPoint);
	});
	TraceUnderMouseTask->ReadyForActivation();
}
void UArcane::OnInputReleased(float TimeHeld)
{
	if (GetCurrentActorInfo()->IsLocallyControlled())
	{
		decal->SetVisibility(false);
		decal->Deactivate();
		decal = nullptr;
		GetCurrentActorInfo()->PlayerController->bShowMouseCursor = true;
	}
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		Target = HitResult;
		UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),Target.ImpactPoint,
			PlayedMontageTag,AnimNotifyTag,STATIC_FUNCTION_FNAME(TEXT("UArcane::OnGameplayEventReceivedFromAnimNotify")));
	});
	TargetDataTask->ReadyForActivation();
}
void UArcane::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	auto temp = UAbilityTask_SendRandomPointsToServer::SendRandomPointsToServer(this,
		Target.ImpactPoint,RadiusOfActivation,GetAbilityLevel());
	temp->OnRandomPoints.AddLambda([this](TArray<FVector> Points)
	{
		for (const auto& Point : Points)
		{
			FGameplayCueParameters Params;
			Params.Location = Point;
			if (GetCurrentActorInfo()->IsNetAuthority())
			{
				UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(GetAvatarActorFromActorInfo(),ArcaneCueTag,Params);
				UAuraFunctionLibrary::ApplyRadialDamageEffectWithFallOff(GetAvatarActorFromActorInfo(),TArray{GetAvatarActorFromActorInfo()},
					Point,RadiusOfActivation/2,RadiusOfActivation,DamageEffectTag,GetAbilityLevel(),GetAbilityLevel()-1);
			}
			else
				UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),ArcaneCueTag,Params);
		}
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	});
	temp->ReadyForActivation();
}
