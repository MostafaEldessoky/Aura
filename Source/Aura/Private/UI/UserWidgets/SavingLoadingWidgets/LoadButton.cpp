// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/LoadButton.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void ULoadButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LoadButton->OnClicked.AddDynamic(this, &ULoadButton::OnLoadButtonClicked);
}

void ULoadButton::OnLoadButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleLoadWidget.Broadcast();
}