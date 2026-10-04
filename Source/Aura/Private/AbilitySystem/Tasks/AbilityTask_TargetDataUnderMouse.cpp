// Mostafa Eldesouky


#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Tasks/AbilityTask_TraceUnderMouse.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/AuraFunctionLibrary.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(UGameplayAbility* OwnedAbility)
{
	return NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwnedAbility);
}
void UAbilityTask_TargetDataUnderMouse::Activate()
{
	Super::Activate();
	bIsServer = Ability->GetCurrentActorInfo()->IsNetAuthority();
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
		TraceUnderMouse();
	else
	{
		AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddLambda(
			[this](const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag Tag)
		{
			if (ShouldBroadcastAbilityTaskDelegates())
				OnTargetDataUnderMouse.Broadcast(*TargetDataHandle.Data[0].Get()->GetHitResult());
			AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());	
			EndTask();
		});
		if (!AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey()))
			SetWaitingOnRemotePlayerData();
	}
}
void UAbilityTask_TargetDataUnderMouse::TraceUnderMouse()
{
	auto TraceUnderMouseTask = UAbilityTask_TraceUnderMouse::TraceUnderMouse(Ability);
	TraceUnderMouseTask->OnTraceUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		if (!bIsServer)
		{
			FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
			TargetData->HitResult = HitResult;
			FGameplayAbilityTargetDataHandle TargetDataHandle;
			TargetDataHandle.Add(TargetData);
			FScopedPredictionWindow ScopedPredictionKey(AbilitySystemComponent.Get());
			AbilitySystemComponent->ServerSetReplicatedTargetData(
				GetAbilitySpecHandle(),
				GetActivationPredictionKey(),
				TargetDataHandle,
				FGameplayTag(),
				AbilitySystemComponent.Get()->ScopedPredictionKey);
		}
		if (ShouldBroadcastAbilityTaskDelegates())
			OnTargetDataUnderMouse.Broadcast(HitResult);	
		
		EndTask();
	});
	TraceUnderMouseTask->ReadyForActivation();
}
