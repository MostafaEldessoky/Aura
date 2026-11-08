// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/LoadList.h"

#include "Components/ScrollBox.h"
#include "GameMode/AuraSaveGameSlotData.h"
#include "Statics/AuraSubSystem.h"
#include "UI/UserWidgets/SavingLoadingWidgets/LoadWidget.h"

void ULoadList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleLoadWidget.AddLambda([this]()
	{
		if (!bShow)
		{
			SetVisibility(ESlateVisibility::Visible);
			bShow = true;
			SaveGameSlotData = UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGameSlotData;
			if (SaveGameSlotData)
				for (const auto& temp : SaveGameSlotData->SlotData)
					if (ULoadWidget* LoadWidget = CreateWidget<ULoadWidget>(this, LoadWidgetClass))
					{
						LoadWidget->SlotName = temp.Key;
						LoadWidget->bIsReady = true;
						LoadWidgets.Add(LoadWidget);
						ScrollBox->AddChild(LoadWidget);
					}
		}
		else
		{
			SetVisibility(ESlateVisibility::Collapsed);
			bShow = false;
			ScrollBox->ClearChildren();
			for (auto LoadWidget : LoadWidgets)
				LoadWidget->Destruct();
			LoadWidgets.Empty();
		}
	});
}
