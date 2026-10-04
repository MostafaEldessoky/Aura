// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AuraAIController.generated.h"


class UAISenseConfig_Damage;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;

UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAuraAIController();
	virtual FGenericTeamId GetGenericTeamId() const override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Hearing* HearingConfig;
	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Damage* DamageConfig;
	UFUNCTION()
	void OnTargetPerceptionUpdated( AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);
};
