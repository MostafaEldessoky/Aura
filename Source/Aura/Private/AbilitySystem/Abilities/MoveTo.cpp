// Mostafa Eldesouky


#include "AbilitySystem/Abilities/MoveTo.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "AbilitySystem/Tasks/AbilityTask_SendTargetDataToServer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Data/Tags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/AttributeInterface.h"


void UMoveTo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto WaitGameplayEventTraceUnderMouse = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,Aura::Abilities::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->EventReceived.AddDynamic(this,&UMoveTo::TraceUnderMouse);
	WaitGameplayEventTraceUnderMouse->ReadyForActivation();
}
void UMoveTo::TraceUnderMouse(FGameplayEventData Payload)
{
	auto TargetDataTask = UAbilityTask_SendTargetDataToServer::SendTargetDataToServer(this,Payload.TargetData);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FGameplayAbilityTargetDataHandle TargetData)
	{
		Cast<UCharacterMovementComponent>(GetCurrentActorInfo()->MovementComponent.Get())->MaxWalkSpeed = UAuraAttributes::GetMovementSpeedAttribute().GetNumericValue(Cast<IAttributeInterface>(GetAvatarActorFromActorInfo())->GetAuraAttributes());;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetCurrentActorInfo()->PlayerController.Get(), TargetData.Get(0)->GetHitResult()->ImpactPoint);
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
	});
	TargetDataTask->ReadyForActivation();
}
