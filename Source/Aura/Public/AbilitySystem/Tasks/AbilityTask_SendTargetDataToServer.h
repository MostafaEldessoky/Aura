// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SendTargetDataToServer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetDataUnderMouse,FGameplayAbilityTargetDataHandle);

/**
 * 
 */
UCLASS()
class AURA_API UAbilityTask_SendTargetDataToServer : public UAbilityTask
{
	GENERATED_BODY()
public:
	static UAbilityTask_SendTargetDataToServer* SendTargetDataToServer(UGameplayAbility* OwnedAbility,FGameplayAbilityTargetDataHandle& targetData);
	FOnTargetDataUnderMouse OnTargetDataUnderMouse;
protected:
	virtual void Activate() override;
private:
	FGameplayAbilityTargetDataHandle TargetData;
	void SendTraceUnderMouseToServer();
};
