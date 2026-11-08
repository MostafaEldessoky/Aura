// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AuraSaveGameSlotData.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSaveGameSlotData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TMap<FString,int32> SlotData;
};
