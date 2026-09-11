// Mostafa Eldesouky


#include "Statics/AuraSubSystem.h"
#include "Data/AuraData.h"


void UAuraSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	AuraData = Cast<UAuraData>(StaticLoadObject(UAuraData::StaticClass(), nullptr,
		TEXT("/Game/BluePrints/Data/BP_SharedData.BP_SharedData")));
}

