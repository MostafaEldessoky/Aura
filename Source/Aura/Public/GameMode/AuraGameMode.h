// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AuraGameMode.generated.h"

class UAuraSaveGame;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void SaveGame();
	UAuraSaveGame* LoadGame();
};
