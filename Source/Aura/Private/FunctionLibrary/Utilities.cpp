// Mostafa Eldesouky


#include "Statics/Utilities.h"


void UUtilities::Initialize(const UObject* WorldContextObject,std::function<bool()> FuncToCheck, std::function<void()> FuncToCall)
{
	if (!FuncToCheck())
	{
		WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick([WorldContextObject,FuncToCheck,FuncToCall]()
		{
			Initialize(WorldContextObject,FuncToCheck,FuncToCall);
		});
		return;
	}
	FuncToCall();
}
UAuraSubSystem* UUtilities::GetAuraSubSystem(const UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UAuraSubSystem>();
}

