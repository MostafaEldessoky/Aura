// Mostafa Eldesouky


#include "UI/UserWidgets/OnlineWidgets/JoinSessionWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Statics/AuraSubSystem.h"

void UJoinSessionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CallUntilReady();
}
void UJoinSessionWidget::OnJoinSessionButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnlineJoinSession(SessionSearchResult);
}
void UJoinSessionWidget::CallUntilReady()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	 {
		 if (bIsReady)
		 {
			JoinSessionButton->OnClicked.AddDynamic(this, &UJoinSessionWidget::OnJoinSessionButtonClicked);
		 	SessionID->SetText(FText::FromString(SessionSearchResult.Session.OwningUserName));
		 }
		 else
		 	CallUntilReady();
	 });
}
