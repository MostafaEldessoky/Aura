// Mostafa Eldesouky


#include "AbilitySystem/Abilities/PrimaryMoveAttack.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "GameFramework/MovementComponent.h"
#include "Interfaces/Combat.h"
#include "Interfaces/Targetable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectiles/Projectile.h"
#include "Statics/Utilities.h"

UPrimaryMoveAttack::UPrimaryMoveAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(Tags::Inputs::InputActions::AttackMove);
	SetAssetTags(AssetTags);
}
void UPrimaryMoveAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		if (HitResult.GetActor() && HitResult.GetActor()->Implements<UTargetable>())
		{
			TargetLocation = HitResult.GetActor()->GetActorLocation();
			AttackTarget(HitResult);
		}
		else 
			MoveToTarget(HitResult.ImpactPoint);
	});
	TargetDataTask->ReadyForActivation();
}
void UPrimaryMoveAttack::MoveToTarget(FVector ImpactPoint)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetCurrentActorInfo()->PlayerController.Get(), ImpactPoint);
	MoveToTargetEndAbility(ImpactPoint);
}

void UPrimaryMoveAttack::MoveToTargetEndAbility(FVector ImpactPoint)
{
	if ((GetAvatarActorFromActorInfo()->GetActorLocation() - ImpactPoint).Size2D() <= 50.f)
		K2_EndAbility();
	else 
		GetWorld()->GetTimerManager().SetTimerForNextTick([this,ImpactPoint]()
 			{
				MoveToTargetEndAbility(ImpactPoint);
 			});
}

void UPrimaryMoveAttack::AttackTarget(FHitResult HitResult)
{
	if (!((GetAvatarActorFromActorInfo()->GetActorLocation() - HitResult.GetActor()->GetActorLocation()).Size2D() <= AttackRange))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetCurrentActorInfo()->PlayerController.Get(),HitResult.GetActor());
		CheckForTargetRange(HitResult);
		return;
	}
	GetCurrentActorInfo()->MovementComponent.Get()->StopMovementImmediately();
	Cast<ICombat>(GetAvatarActorFromActorInfo())->TargetMotionWarping(HitResult.GetActor()->GetActorLocation());
	auto PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,FName(""),
		UUtilities::GetAuraSubSystem(this)->AuraData->Montages[Tags::Characters::Player].MontageToPlay[Tags::Montages::AttackMontage]);
	PlayMontageAndWait->ReadyForActivation();
	auto WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Tags::EventTasks::SpawnProjectile);
	WaitGameplayEvent->EventReceived.AddDynamic(this,&UPrimaryMoveAttack::OnGameplayEventReceivedFromAnimNotify);
	WaitGameplayEvent->ReadyForActivation();
}
void UPrimaryMoveAttack::CheckForTargetRange(FHitResult HitResult)
{
	if ((GetAvatarActorFromActorInfo()->GetActorLocation() - HitResult.GetActor()->GetActorLocation()).Size2D() <= AttackRange )
		AttackTarget(HitResult);
	else
		GetWorld()->GetTimerManager().SetTimerForNextTick([this,HitResult]()
    		{
    			CheckForTargetRange(HitResult);
    		});
}
void UPrimaryMoveAttack::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	auto SpawnedActor = GetWorld()->SpawnActorDeferred<AProjectile>(
		 UUtilities::GetAuraSubSystem(this)->AuraData->ProjectileData.ProjectileAssets[Tags::Projectiles::FireBall].ProjectileClass,
		 Cast<ICombat>(GetAvatarActorFromActorInfo())->GetWeaponSocketTransform(),
		 GetAvatarActorFromActorInfo()
		 );
	SpawnedActor->ProjectileEffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		UUtilities::GetAuraSubSystem(this)->AuraData->ProjectileData.ProjectileAssets[Tags::Projectiles::FireBall].ProjectileEffect,
		GetAbilityLevel(),
		GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
	SpawnedActor->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Cast<ICombat>(GetAvatarActorFromActorInfo())->GetWeaponSocketTransform().GetLocation(),TargetLocation));
	SpawnedActor->FinishSpawning(Cast<ICombat>(GetAvatarActorFromActorInfo())->GetWeaponSocketTransform());
	K2_EndAbility();
}
