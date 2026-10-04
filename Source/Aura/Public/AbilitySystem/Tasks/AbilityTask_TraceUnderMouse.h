// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TraceUnderMouse.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTraceUnderMouseDelegate, FHitResult);
/**
 * 
 */
UCLASS()
class AURA_API UAbilityTask_TraceUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
	static UAbilityTask_TraceUnderMouse* TraceUnderMouse(UGameplayAbility* OwningAbility);
	FOnTraceUnderMouseDelegate OnTraceUnderMouse;
protected:
	virtual void Activate() override;
private:
	FHitResult HitResult;
	void TraceUnderMouse();
	static TMap<UAbilitySystemComponent*,UAbilityTask_TraceUnderMouse*> AbilityTaskMap;
};
