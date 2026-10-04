// Mostafa Eldesouky


#include "AbilitySystem/Abilities/FireBall.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_CanAttack.h"
#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"
#include "Kismet/KismetMathLibrary.h"
#include "Statics/AuraFunctionLibrary.h"
#include "Statics/AuraSubSystem.h"

void UFireBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
	CombatInterface = GetAvatarActorFromActorInfo();
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		auto CanAttack = UAbilityTask_CanAttack::GetCanAttack(this,HitResult);
		CanAttack->OnCanAttack.AddLambda([this,HitResult]()
		{
			Target = HitResult;
			UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),HitResult.GetActor()->GetActorLocation(),
				PlayedMontageTag,AnimNotifyTag,STATIC_FUNCTION_FNAME(TEXT("UTrowFollowUpProjectile::OnGameplayEventReceivedFromAnimNotify")));
		});
		CanAttack->ReadyForActivation();
	});
	TargetDataTask->ReadyForActivation();
}
void UFireBall::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	AActor* TargetActor = nullptr;
	if (bHoming)
		TargetActor = Target.GetActor();
	if (GetAbilityLevel() <= 1)
		UAuraFunctionLibrary::SpawnProjectile(GetAvatarActorFromActorInfo(),TargetActor,Target.GetActor()->GetActorLocation(),ProjectileID,5.f,false,GetAbilityLevel());
	else
	{
		auto OwnerRightVector = FVector(GetAvatarActorFromActorInfo()->GetActorRightVector().X , GetAvatarActorFromActorInfo()->GetActorRightVector().Y ,0) * 100;
		for (const auto& temp : UAuraFunctionLibrary::GetBoundedVectors(
			 -OwnerRightVector ,OwnerRightVector ,CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),GetAbilityLevel()))
		{
			DrawDebugLine(GetWorld(),CombatInterface->GetWeaponMechanicSocketTransform().GetLocation(),temp,FColor::Green,true);
			UAuraFunctionLibrary::SpawnProjectile(GetAvatarActorFromActorInfo(),TargetActor,temp,ProjectileID,5.f,false,GetAbilityLevel());
		}
	}
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
}


