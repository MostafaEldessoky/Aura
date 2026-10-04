// Mostafa Eldesouky


#include "AbilitySystem/Tasks/AbilityTask_SendRandomPointsToServer.h"
#include "AbilitySystemComponent.h"
#include "Statics/AuraFunctionLibrary.h"


UAbilityTask_SendRandomPointsToServer* UAbilityTask_SendRandomPointsToServer::SendRandomPointsToServer(
	UGameplayAbility* OwningAbility, FVector originPoint, float radiusOfActivation, int32 level)
{
	auto TaskObj = NewAbilityTask<UAbilityTask_SendRandomPointsToServer>(OwningAbility);
	TaskObj->OriginPoint = originPoint;
	TaskObj->RadiusOfActivation = radiusOfActivation;
	TaskObj->Level = level;
	return TaskObj;
}
void UAbilityTask_SendRandomPointsToServer::Activate()
{
	Super::Activate();
	UAuraFunctionLibrary::CallFuncOnPointsCollectedOnTheGround(Ability,false,OriginPoint,RadiusOfActivation,
		[this](TArray<FVector> Points)
		{
			if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
			{
				auto temp = TArray<FVector>();
				if (!Ability->GetCurrentActorInfo()->IsNetAuthority())
				{
					FGameplayAbilityTargetDataHandle TargetDataHandle;
					for (int32 i = 0; i < Level && Points.IsValidIndex(i); ++i)
					{
						temp.Add(Points[i]);
						FGameplayAbilityTargetData_LocationInfo* TargetData = new FGameplayAbilityTargetData_LocationInfo();
						TargetData->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
						TargetData->TargetLocation.LiteralTransform = FTransform(Points[i]);
						TargetDataHandle.Add(TargetData);
					}
					if (ShouldBroadcastAbilityTaskDelegates())
						OnRandomPoints.Broadcast(temp);
					FScopedPredictionWindow ScopedPredictionKey(AbilitySystemComponent.Get());
					AbilitySystemComponent->ServerSetReplicatedTargetData(
						GetAbilitySpecHandle(),
						GetActivationPredictionKey(),
						TargetDataHandle,
						FGameplayTag(),
						AbilitySystemComponent.Get()->ScopedPredictionKey);
				}
				else
				{
					for (int32 i = 0; i < Level && Points.IsValidIndex(i); ++i)
						temp.Add(Points[i]);
					if (ShouldBroadcastAbilityTaskDelegates())
						OnRandomPoints.Broadcast(temp);
				}
				EndTask();
			}
			else
			{
				AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddLambda(
					[this](const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag Tag)
				{
					auto temp = TArray<FVector>();
					for (const auto& Data : TargetDataHandle.Data)
						if (Data.IsValid())
							temp.Add(Data->GetEndPointTransform().GetLocation());
					if (ShouldBroadcastAbilityTaskDelegates())
						OnRandomPoints.Broadcast(temp);
					AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());	
					EndTask();
				});
				if (!AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey()))
					SetWaitingOnRemotePlayerData();
			}
		});
}
