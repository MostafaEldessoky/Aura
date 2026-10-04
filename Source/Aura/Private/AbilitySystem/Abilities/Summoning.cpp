// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Summoning.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "Characters/Enemy/AuraEnemyBase.h"
#include "Statics/AuraFunctionLibrary.h"


void USummoning::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo);
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),HitResult.ImpactPoint,
			PlayedMontageTag,AnimNotifyTag,STATIC_FUNCTION_FNAME(TEXT("USummoning::OnGameplayEventReceivedFromAnimNotify")));
	});
	TargetDataTask->ReadyForActivation();
}

void USummoning::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	if (GetCurrentActorInfo()->IsNetAuthority())
		UAuraFunctionLibrary::CallFuncOnPointsCollectedOnTheGround(this,true,
			GetAvatarActorFromActorInfo()->GetActorLocation(),200,[this](TArray<FVector>& Points)
			{
				if (Points.IsEmpty()) return;
				GetWorld()->SpawnActor<AAuraEnemyBase>(EnemyClasses[FMath::RandRange(0,EnemyClasses.Num()-1)],
					Points[FMath::RandRange(0,Points.Num()-1)],GetAvatarActorFromActorInfo()->GetActorRotation());
			});
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}
