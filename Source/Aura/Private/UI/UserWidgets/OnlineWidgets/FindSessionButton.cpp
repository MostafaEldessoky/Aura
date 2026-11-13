// Mostafa Eldesouky


#include "UI/UserWidgets/OnlineWidgets/FindSessionButton.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void UFindSessionButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	FindSessionButton->OnClicked.AddDynamic(this, &UFindSessionButton::OnFindSessionButtonClicked);
}

void UFindSessionButton::OnFindSessionButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleFindSessionWidget.Broadcast();
}
