// Mostafa Eldesouky


#include "Statics/AuraSubSystem.h"
#include "Data/AuraData.h"


UAuraSubSystem* UAuraSubSystem::GetAuraSubSystem(const UObject* WorldContextObject)
{
	auto GameInstanceObj = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UAuraSubSystem>();
	if (!GameInstanceObj->AuraData)
		GameInstanceObj->AuraData = Cast<UAuraData>(StaticLoadObject(UAuraData::StaticClass(), nullptr,
			TEXT("/Game/BluePrints/Data/BP_SharedData.BP_SharedData")));
	return GameInstanceObj;
}
