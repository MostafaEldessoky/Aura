// Mostafa Eldesouky


#include "AbilitySystem/Abilities/FireBall.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_CanAttack.h"
#include "AbilitySystem/Tasks/AbilityTask_SendTargetDataToServer.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraFunctionLibrary.h"



void UFireBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CombatInterface = GetAvatarActorFromActorInfo();
	auto WaitGameplayEventTraceUnderMouse = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Aura::Abilities::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->EventReceived.AddDynamic(this,&UFireBall::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->ReadyForActivation();
}
void UFireBall::TraceUnderMouse(FGameplayEventData Payload)
{
	if (bOneTrace) return;
	bOneTrace = true;
	auto TargetDataTask = UAbilityTask_SendTargetDataToServer::SendTargetDataToServer(this,Payload.TargetData);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FGameplayAbilityTargetDataHandle TargetData)
	{
		Target = *TargetData.Get(0)->GetHitResult();
		auto CanAttack = UAbilityTask_CanAttack::GetCanAttack(this,*TargetData.Get(0)->GetHitResult());
		CanAttack->OnCanAttack.AddLambda([this]()
		{
			UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),Target.GetActor()->GetActorLocation(),
				PlayedMontageTag,AnimNotifyTag,STATIC_FUNCTION_FNAME(TEXT("UTrowFollowUpProjectile::OnGameplayEventReceivedFromAnimNotify")));
		});
		CanAttack->ReadyForActivation();
	});
	TargetDataTask->ReadyForActivation();
}

void UFireBall::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	bOneTrace = false;
	AActor* TargetActor = nullptr;
	if (bHoming)
		TargetActor = Target.GetActor();
	if (GetAbilityLevel() <= 1)
		UAuraFunctionLibrary::SpawnProjectile(GetAvatarActorFromActorInfo(),TargetActor,Target.GetActor()->GetActorLocation(),ProjectileID,5.f,false,false,GetAssetTags().First(),GetAbilityLevel());
	else
	{
		auto OwnerRightVector = FVector(GetAvatarActorFromActorInfo()->GetActorRightVector().X , GetAvatarActorFromActorInfo()->GetActorRightVector().Y ,0) * 100;
		for (const auto& temp : UAuraFunctionLibrary::GetBoundedVectors(
			 -OwnerRightVector ,OwnerRightVector ,CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),GetAbilityLevel()))
		{
			DrawDebugLine(GetWorld(),CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),temp,FColor::Green,true);
			UAuraFunctionLibrary::SpawnProjectile(GetAvatarActorFromActorInfo(),TargetActor,temp,ProjectileID,5.f,false,false,GetAssetTags().First(),GetAbilityLevel());
		}
	}
	CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}


