// Mostafa Eldesouky


#include "AbilitySystem/Tasks/AbilityTask_TraceUnderMouse.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"

TMap<UAbilitySystemComponent*,UAbilityTask_TraceUnderMouse*> UAbilityTask_TraceUnderMouse::AbilityTaskMap;
UAbilityTask_TraceUnderMouse* UAbilityTask_TraceUnderMouse::TraceUnderMouse(UGameplayAbility* OwningAbility)
{
	auto ASC = OwningAbility->GetAbilitySystemComponentFromActorInfo();
	auto Task = AbilityTaskMap.Find(ASC);
	if(Task) return *Task;
	auto TaskObj = NewAbilityTask<UAbilityTask_TraceUnderMouse>(OwningAbility);
	AbilityTaskMap.Add(ASC, TaskObj);
	return TaskObj;
}

void UAbilityTask_TraceUnderMouse::Activate()
{
	Super::Activate();
	TraceUnderMouse();
}
void UAbilityTask_TraceUnderMouse::TraceUnderMouse()
{
	if (Ability)
	{
		Ability->GetCurrentActorInfo()->PlayerController.Get()->GetHitResultUnderCursor(
			UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.MouseTraceChannel,
			false,HitResult);
		OnTraceUnderMouse.Broadcast(HitResult);
	}
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			TraceUnderMouse();
		});
}
