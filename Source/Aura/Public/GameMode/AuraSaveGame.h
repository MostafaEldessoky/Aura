// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameplayTags.h"
#include "AuraSaveGame.generated.h"

USTRUCT() struct FCharacterSaveGame
{
	GENERATED_BODY()
	UPROPERTY()
	float Health;
	UPROPERTY()
	float Mana;
};
USTRUCT() struct FAbilitiesSaveGame
{
	GENERATED_BODY()
	UPROPERTY()
	FGameplayTag AbilityTag;
	UPROPERTY()
	FGameplayTag InputTag;
	UPROPERTY()
	int32 AbilityLevel;
};
USTRUCT() struct FPlayerSaveGame 
{
	GENERATED_BODY()
	UPROPERTY()
	float XP;
	UPROPERTY()
	float Strength;
	UPROPERTY()
	float Agility;
	UPROPERTY()
	float Intelligence;
	UPROPERTY()
	TArray<FAbilitiesSaveGame> AbilitiesSaveGame;
};

USTRUCT() struct FSaveGameBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGameplayTag ID;
	UPROPERTY()
	bool bIsDestroyed;
	UPROPERTY()
	FTransform Transform;
	UPROPERTY()
	FCharacterSaveGame CharacterSaveGame;
	UPROPERTY()
	FPlayerSaveGame  PlayerSaveGame;
};


/**
 * 
 */
UCLASS()
class AURA_API UAuraSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	TSoftObjectPtr<UWorld> Level;
	UPROPERTY(SaveGame)
	TArray<FSaveGameBase> ObjectData;
};
