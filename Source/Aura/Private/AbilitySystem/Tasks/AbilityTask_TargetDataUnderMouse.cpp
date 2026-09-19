// Mostafa Eldesouky


#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
#include "Data/AuraData.h"
#include "Statics/Utilities.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(UGameplayAbility* OwnedAbility)
{
	return NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwnedAbility);
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
	Super::Activate();
	
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
		TraceUnderMouse();
	else
	{
		AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddLambda(
			[this](const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag Tag)
		{
			AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());	
			if (ShouldBroadcastAbilityTaskDelegates())
				OnTargetDataUnderMouse.Broadcast(*TargetDataHandle.Data[0].Get()->GetHitResult());
			EndTask();
		});
		if (!AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey()))
			SetWaitingOnRemotePlayerData();
	}
}

void UAbilityTask_TargetDataUnderMouse::TraceUnderMouse()
{
	FHitResult HitResult;
	Ability->GetCurrentActorInfo()->PlayerController.Get()->GetHitResultUnderCursor(
		UUtilities::GetAuraSubSystem(this)->AuraData->PlayerData.TraceChannel,false,HitResult);
	
	if (ShouldBroadcastAbilityTaskDelegates())
		OnTargetDataUnderMouse.Broadcast(HitResult);	
	
	if (Ability->GetCurrentActorInfo()->IsNetAuthority())
	{
		EndTask();
		return;
	}
	
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
	EndTask();
}
