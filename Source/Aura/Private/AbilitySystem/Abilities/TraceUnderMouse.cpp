// Mostafa Eldesouky


#include "AbilitySystem/Abilities/TraceUnderMouse.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "Statics/AuraSubSystem.h"

void UTraceUnderMouse::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	TraceUnderMouse();
}
void UTraceUnderMouse::TraceUnderMouse()
{
	FHitResult HitResult;
	GetCurrentActorInfo()->PlayerController.Get()->GetHitResultUnderCursor(
		UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.MouseTraceChannel,
		false,HitResult);
	FGameplayEventData EventData;
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
	EventData.TargetData.Add(TargetData);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(),Aura::Abilities::TraceUnderMouse,EventData);
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			TraceUnderMouse();
		});
}

