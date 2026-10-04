// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_CanAttack.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnCanAttack);
/**
 * 
 */
UCLASS()
class AURA_API UAbilityTask_CanAttack : public UAbilityTask
{
	GENERATED_BODY()
public:
	static UAbilityTask_CanAttack* GetCanAttack(UGameplayAbility* OwnedAbility,FHitResult Hit);
	FOnCanAttack OnCanAttack;
protected:
	virtual void Activate() override;
private:
	FHitResult HitResult;
	float AttackRange;
	void CheckForTargetRange();
	void OnTargetInRange();
};
