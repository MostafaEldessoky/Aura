// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SendRandomPointsToServer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRandomPoints, TArray<FVector>);
/**
 * 
 */
UCLASS()
class AURA_API UAbilityTask_SendRandomPointsToServer : public UAbilityTask
{
	GENERATED_BODY()
public:
	static UAbilityTask_SendRandomPointsToServer* SendRandomPointsToServer(UGameplayAbility* OwningAbility,FVector originPoint,
	float radiusOfActivation, int32 level);
	FOnRandomPoints OnRandomPoints;
protected:
	virtual void Activate() override;
private:
	FVector OriginPoint;
	float RadiusOfActivation;
	int32 Level;
};
