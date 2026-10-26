// Mostafa Eldesouky


#include "UI/UserWidgets/MainWidget/MainWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Statics/AuraSubSystem.h"


void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleAttributeWidget.AddLambda([this]()
	{
		if (!bIsAttributeWidgetVisible)
		{
			AttributeWidget->SetVisibility(ESlateVisibility::Visible);
			bIsAttributeWidgetVisible = true;
		}
		else
		{
			AttributeWidget->SetVisibility(ESlateVisibility::Collapsed);
			bIsAttributeWidgetVisible = false;
		}
	});
	UAuraSubSystem::GetAuraSubSystem(this)->OnToggleSpellTreeWidget.AddLambda([this]()
	{
		if (!bIsSpellTreeWidgetVisible)
		{
			SpellTreeWidget->SetVisibility(ESlateVisibility::Visible);
			bIsSpellTreeWidgetVisible = true;
		}
		else
		{
			SpellTreeWidget->SetVisibility(ESlateVisibility::Collapsed);
			bIsSpellTreeWidgetVisible = false;
		}
	});
}

bool UMainWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                               UDragDropOperation* InOperation)
{
	InOperation->Tag = "";
	InOperation->DefaultDragVisual = nullptr;
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
