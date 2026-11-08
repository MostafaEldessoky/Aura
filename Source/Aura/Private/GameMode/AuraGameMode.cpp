// Mostafa Eldesouky


#include "GameMode/AuraGameMode.h"

#include "Data/Tags.h"
#include "Engine/TargetPoint.h"
#include "Statics/AuraSubSystem.h"


void AAuraGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	auto SaveGame = UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGame;
	if (SaveGame) 
		for (const auto& temp : SaveGame->ObjectData)
			if (temp.ID == Aura::Characters::Player)
			{
				TargetPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass());
				TargetPoint->SetActorTransform(temp.Transform);
				Super::RestartPlayerAtPlayerStart(NewPlayer, TargetPoint);
				return;
			}
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}
