// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/LoadWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Statics/AuraSubSystem.h"


void ULoadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CallUntilReady();
}

void ULoadWidget::OnLoadButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnLoadGameSlotSelected.Broadcast(SlotName,0);
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleLoadWidget.Broadcast();
}

void ULoadWidget::OnDeleteButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnLoadGameSlotDeleted.Broadcast(SlotName,0);
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleLoadWidget.Broadcast();
}

void ULoadWidget::CallUntilReady()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
 	{
 		if (bIsReady)
 		{
 			LoadButton->OnClicked.AddDynamic(this, &ULoadWidget::OnLoadButtonClicked);
			DeleteButton->OnClicked.AddDynamic(this, &ULoadWidget::OnDeleteButtonClicked);
 			SlotData->SetText(FText::FromString(SlotName));
 		}
 		else
 			CallUntilReady();
 	});
}


