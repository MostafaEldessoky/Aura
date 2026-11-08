// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Highlights.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"


void UHighlights::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto WaitGameplayEventTraceUnderMouse = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Aura::Abilities::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->EventReceived.AddDynamic(this,&UHighlights::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->ReadyForActivation();
	auto temp = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Aura::InputActions::RMB);
	temp->EventReceived.AddDynamic(this,&UHighlights::OnRMBPressed);
	temp->ReadyForActivation();
}
void UHighlights::OnRMBPressed(FGameplayEventData Payload)
{
	if (IsValid(CurrentTarget.GetObject()))
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(),Aura::Abilities::Attack::FireBall,Payload);
	else
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(),Aura::Abilities::MoveTo,Payload);
}
void UHighlights::TraceUnderMouse(FGameplayEventData Payload)
{
	AActor* HitActor = nullptr;
	if (Payload.TargetData.Num() > 0 && Payload.TargetData.Get(0) && Payload.TargetData.Get(0)->GetHitResult())
	{
		HitActor = Payload.TargetData.Get(0)->GetHitResult()->GetActor();
	}

	CurrentTarget = (HitActor && HitActor->Implements<UCombat>()) ? HitActor : nullptr;

	if (CurrentTarget != LastTarget)
	{
		if (IsValid(LastTarget.GetObject()))
		{
			LastTarget->UnHighlight();
		}
		if (IsValid(CurrentTarget.GetObject()))
		{
			CurrentTarget->Highlight();
		}
		LastTarget = CurrentTarget;
	}
}

