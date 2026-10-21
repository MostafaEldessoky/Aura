// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "DeathBehavior.generated.h"

class ICombat;
/**
 * 
 */
UCLASS()
class AURA_API UDeathBehavior : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
};
