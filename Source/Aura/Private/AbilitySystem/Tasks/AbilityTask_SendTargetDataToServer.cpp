// Mostafa Eldesouky


#include "AbilitySystem/Tasks/AbilityTask_SendTargetDataToServer.h"
#include "AbilitySystemComponent.h"

UAbilityTask_SendTargetDataToServer* UAbilityTask_SendTargetDataToServer::SendTargetDataToServer(UGameplayAbility* OwnedAbility,FGameplayAbilityTargetDataHandle& targetData)
{
	auto TaskObj = NewAbilityTask<UAbilityTask_SendTargetDataToServer>(OwnedAbility);
	TaskObj->TargetData = targetData;
	return TaskObj;
}
void UAbilityTask_SendTargetDataToServer::Activate()
{
	Super::Activate();
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
		SendTraceUnderMouseToServer();
	else
	{
		AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddLambda(
			[this](const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag Tag)
		{
			if (ShouldBroadcastAbilityTaskDelegates())
				OnTargetDataUnderMouse.Broadcast(TargetDataHandle);
			AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());	
			EndTask();
		});
		if (!AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey()))
			SetWaitingOnRemotePlayerData();
	}
}
void UAbilityTask_SendTargetDataToServer::SendTraceUnderMouseToServer()
{
	FScopedPredictionWindow ScopedPredictionKey(AbilitySystemComponent.Get());
	AbilitySystemComponent.Get()->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetData,
		FGameplayTag(),
		AbilitySystemComponent.Get()->ScopedPredictionKey);
	if (ShouldBroadcastAbilityTaskDelegates())
		OnTargetDataUnderMouse.Broadcast(TargetData);
	EndTask();
}
