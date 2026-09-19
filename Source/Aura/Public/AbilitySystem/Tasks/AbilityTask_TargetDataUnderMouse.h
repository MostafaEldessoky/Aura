// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TargetDataUnderMouse.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetDataUnderMouse,FHitResult);

/**
 * 
 */
UCLASS()
class AURA_API UAbilityTask_TargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
	static UAbilityTask_TargetDataUnderMouse* GetTargetDataUnderMouse(UGameplayAbility* OwnedAbility);
	FOnTargetDataUnderMouse OnTargetDataUnderMouse;
protected:
	virtual void Activate() override;
private:
	void TraceUnderMouse();
};
