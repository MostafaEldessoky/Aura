// Mostafa Eldesouky


#include "AbilitySystem/Abilities/KnockBack.h"

#include "GameFramework/Character.h"

void UKnockBack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Cast<ACharacter>(GetAvatarActorFromActorInfo())->LaunchCharacter(FVector(0.f, 0.f, 1000.f), false, true);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
