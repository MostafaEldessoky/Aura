// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/SaveButton.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void USaveButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SaveButton->OnClicked.AddDynamic(this, &USaveButton::OnSaveButtonClicked);
}
void USaveButton::OnSaveButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleSaveWidget.Broadcast();
}