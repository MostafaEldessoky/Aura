// Mostafa Eldesouky


#include "UI/UserWidgets/Button/BottonWidget.h"

#include "Components/Button.h"
#include "Statics/Utilities.h"

void UBottonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddDynamic(this,&UBottonWidget::LevelUp);
}

void UBottonWidget::LevelUp()
{
	UUtilities::GetAuraSubSystem(this)->OnNeedLevelUpAttribute.Broadcast(Attribute);
}
