// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/SaveWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Statics/AuraSubSystem.h"

void USaveWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SlotName->OnTextCommitted.AddDynamic(this, &USaveWidget::OnSlotNameTextCommitted);
	SaveButton->OnClicked.AddDynamic(this, &USaveWidget::OnSaveButtonClicked);
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleSaveWidget.AddLambda([this]()
	{
		if (!bShow)
		{
			SetVisibility(ESlateVisibility::Visible);
			bShow = true;
		}
		else
		{
			SetVisibility(ESlateVisibility::Collapsed);
			bShow = false;
		}
	});
}

void USaveWidget::OnSlotNameTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	SlotNameText = Text.ToString();
}
void USaveWidget::OnSaveButtonClicked()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnSaveGameToSlotNeeded.Broadcast(SlotNameText, 0);
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleSaveWidget.Broadcast();
	SlotName->SetText(FText::FromString(""));
}
