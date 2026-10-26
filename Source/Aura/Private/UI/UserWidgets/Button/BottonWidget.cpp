// Mostafa Eldesouky


#include "UI/UserWidgets/Button/BottonWidget.h"

#include "Components/Button.h"
#include "Statics/AuraSubSystem.h"

void UBottonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddDynamic(this,&UBottonWidget::LevelUp);
}

void UBottonWidget::LevelUp()
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnNeedLevelUpAttribute.Broadcast(Attribute.GetName());
}
