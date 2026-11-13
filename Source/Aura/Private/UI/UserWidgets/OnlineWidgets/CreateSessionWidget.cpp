// Mostafa Eldesouky


#include "UI/UserWidgets/OnlineWidgets/CreateSessionWidget.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void UCreateSessionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CreateSessionButton->OnClicked.AddDynamic(this, &UCreateSessionWidget::OnCreateSessionButtonClicked);
}

void UCreateSessionWidget::OnCreateSessionButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnlineCreateSession();
}
