// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/Continue.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void UContinue::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LoadButton->OnClicked.AddDynamic(this, &UContinue::OnLoadButtonClicked);
}

void UContinue::OnLoadButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnLoadGameSlotSelected.Broadcast("CONTINUE",0);
}
