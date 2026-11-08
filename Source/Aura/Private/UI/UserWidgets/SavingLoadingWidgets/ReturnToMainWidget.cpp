// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/ReturnToMainWidget.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"
#include "UI/UserWidgets/SavingLoadingWidgets/SaveWidget.h"

void UReturnToMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SaveButton->OnClicked.AddDynamic(this, &UReturnToMainWidget::OnSaveButtonClicked);
}
void UReturnToMainWidget::OnSaveButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnSaveGameToSlotNeeded.Broadcast("CONTINUE", 0);
	UAuraSubSystem::GetAuraSubSystem(this)->OpenMap(Level);
}