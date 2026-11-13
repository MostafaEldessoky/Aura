// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AuraOnlineGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraOnlineGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
private:
	int8 PlayerCounter;
	UPROPERTY(EditDefaultsOnly, Category = "CPPVars")
	int8 MaxPlayers;
	UPROPERTY(EditDefaultsOnly, Category = "CPPVars")
	FString MapName;
};
