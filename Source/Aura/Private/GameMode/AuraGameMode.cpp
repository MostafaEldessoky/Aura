// Mostafa Eldesouky


#include "GameMode/AuraGameMode.h"

#include "GameMode/AuraSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AAuraGameMode::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("SaveSlot", 0))
		UGameplayStatics::DeleteGameInSlot("SaveSlot", 0);
	auto SaveGame = UGameplayStatics::CreateSaveGameObject(UAuraSaveGame::StaticClass());
	UGameplayStatics::SaveGameToSlot(SaveGame, "SaveSlot", 0);
}

UAuraSaveGame* AAuraGameMode::LoadGame()
{
	return Cast<UAuraSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
}
