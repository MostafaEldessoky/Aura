// Mostafa Eldesouky


#include "GameMode/AuraOnlineGameMode.h"

#include "Statics/AuraSubSystem.h"

void AAuraOnlineGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerCounter++;
	if (PlayerCounter == MaxPlayers)
	{
		UAuraSubSystem::GetAuraSubSystem(this)->OnlineStartSession(MapName+"?Listen");
	}
}
