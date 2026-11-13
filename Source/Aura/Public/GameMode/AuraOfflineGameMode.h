// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AuraOfflineGameMode.generated.h"

class ATargetPoint;
class UAuraSaveGame;
/**
 * 
 */
UCLASS()
class AURA_API AAuraOfflineGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;
private:
	UPROPERTY()
	ATargetPoint* TargetPoint;
};
