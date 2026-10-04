// Mostafa Eldesouky

#include "AbilitySystem/Abilities/StopMove.h"
#include "GameFramework/MovementComponent.h"

void UStopMove::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GetCurrentActorInfo()->MovementComponent.Get()->StopMovementImmediately();
	EndAbility(Handle,ActorInfo,ActivationInfo,false,false);
}
