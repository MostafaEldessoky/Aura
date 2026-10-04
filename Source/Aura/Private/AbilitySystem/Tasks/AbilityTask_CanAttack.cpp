// Mostafa Eldesouky


#include "AbilitySystem/Tasks/AbilityTask_CanAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "Interfaces/AttributeInterface.h"
#include "Data/Tags.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/AuraFunctionLibrary.h"

UAbilityTask_CanAttack* UAbilityTask_CanAttack::GetCanAttack(UGameplayAbility* OwnedAbility,FHitResult Hit)
{
	auto TaskObj = NewAbilityTask<UAbilityTask_CanAttack>(OwnedAbility);
	TaskObj->HitResult = Hit;
	return TaskObj;
}

void UAbilityTask_CanAttack::Activate()
{
	Super::Activate();
	AttackRange = UAuraAttributes::GetAttackRangeAttribute().GetNumericValue(Cast<IAttributeInterface>(Ability->GetAvatarActorFromActorInfo())->GetAuraAttributes());
	if (!((Ability->GetAvatarActorFromActorInfo()->GetActorLocation() - HitResult.GetActor()->GetActorLocation()).Size2D() <= AttackRange))
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
		TargetData->HitResult = HitResult;
		FGameplayEventData EventData;
		EventData.TargetData.Add(TargetData);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			AbilitySystemComponent->GetAvatarActor(),
			Aura::Abilities::MoveTo,
			EventData);
		CheckForTargetRange();
	}
	else
		OnTargetInRange();
}
void UAbilityTask_CanAttack::CheckForTargetRange()
{
	if ((Ability->GetAvatarActorFromActorInfo()->GetActorLocation() - HitResult.GetActor()->GetActorLocation()).Size2D() <= AttackRange )
		OnTargetInRange();
	else
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			CheckForTargetRange();
		});
}

void UAbilityTask_CanAttack::OnTargetInRange()
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),Aura::Abilities::StopMove,FGameplayEventData());
	if (ShouldBroadcastAbilityTaskDelegates()) OnCanAttack.Broadcast();
 	EndTask();
}
