// Mostafa Eldesouky


#include "UI/UserWidgets/OnlineWidgets/LeaveSession.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void ULeaveSession::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LeaveSessionButton->OnClicked.AddDynamic(this, &ULeaveSession::OnLeaveSessionButtonClicked);
}

void ULeaveSession::OnLeaveSessionButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnlineDestroySession();
}
