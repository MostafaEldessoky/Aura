// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AuraGameMode.generated.h"

class ATargetPoint;
class UAuraSaveGame;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;
private:
	UPROPERTY()
	ATargetPoint* TargetPoint;
};
