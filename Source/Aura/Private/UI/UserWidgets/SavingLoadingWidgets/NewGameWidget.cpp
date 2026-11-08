// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/NewGameWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Statics/AuraSubSystem.h"

void UNewGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	NewGame->OnClicked.AddDynamic(this, &UNewGameWidget::OnNewGameClicked);
}

void UNewGameWidget::OnNewGameClicked()
{
	if (UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGame)
		UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGame->MarkAsGarbage();
	UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGame = nullptr;
	UAuraSubSystem::GetAuraSubSystem(this)->OpenMap(Level);
}

