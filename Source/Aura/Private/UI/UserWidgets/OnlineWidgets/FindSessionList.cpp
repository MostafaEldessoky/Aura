// Mostafa Eldesouky


#include "UI/UserWidgets/OnlineWidgets/FindSessionList.h"

#include "OnlineSessionSettings.h"
#include "Components/ScrollBox.h"
#include "Statics/AuraSubSystem.h"
#include "UI/UserWidgets/OnlineWidgets/JoinSessionWidget.h"

void UFindSessionList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleFindSessionWidget.AddLambda([this]()
	{
		if (!bShow)
		{
			SetVisibility(ESlateVisibility::Visible);
			bShow = true;
			UAuraSubSystem::GetAuraSubSystem(this)->OnListOfSessions.AddLambda([this](FOnlineSessionSearchResult SessionSearchResult)
			{
				if (UJoinSessionWidget* JoinSessionWidget = CreateWidget<UJoinSessionWidget>(this, JoinSessionWidgetClass))
				{
					JoinSessionWidget->SessionSearchResult = SessionSearchResult;
					JoinSessionWidget->bIsReady = true;
					JoinSessionWidgets.Add(JoinSessionWidget);
					ScrollBox->AddChild(JoinSessionWidget);
				}
			});
			UAuraSubSystem::GetAuraSubSystem(this)->OnlineFindSession();
		}
		else
		{
			SetVisibility(ESlateVisibility::Collapsed);
			bShow = false;
			ScrollBox->ClearChildren();
			for (auto JoinSessionWidget : JoinSessionWidgets)
				JoinSessionWidget->Destruct();
			JoinSessionWidgets.Empty();
		}
	});
}
