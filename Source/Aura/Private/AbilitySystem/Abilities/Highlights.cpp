// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Highlights.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Tasks/AbilityTask_TraceUnderMouse.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"


void UHighlights::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	TraceUnderMouse();
	auto temp = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Aura::InputActions::RMB);
	temp->EventReceived.AddDynamic(this,&UHighlights::OnRMBPressed);
	temp->ReadyForActivation();
}
void UHighlights::OnRMBPressed(FGameplayEventData Payload)
{
	if (CurrentTarget)
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(),Aura::Abilities::PrimaryAttack,Payload);
	else
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(),Aura::Abilities::MoveTo,Payload);
}
void UHighlights::TraceUnderMouse()
{
 	auto TraceUnderMouseTask = UAbilityTask_TraceUnderMouse::TraceUnderMouse(this);
 	TraceUnderMouseTask->OnTraceUnderMouse.AddLambda([this](FHitResult HitResult)
 	{
		CurrentTarget = HitResult.GetActor();
		if (CurrentTarget)
		{
			CurrentTarget->Highlight();
			LastTarget = CurrentTarget;
			if (LastTarget && LastTarget != CurrentTarget)
				LastTarget->UnHighlight();
		}
		else if (LastTarget)
			LastTarget->UnHighlight();
 	});
 	TraceUnderMouseTask->ReadyForActivation();
}

