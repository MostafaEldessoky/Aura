// Mostafa Eldesouky


#include "AbilitySystem/Abilities/MoveTo.h"

#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


void UMoveTo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetCurrentActorInfo()->PlayerController.Get(), HitResult.ImpactPoint);
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	});
	TargetDataTask->ReadyForActivation();
}
