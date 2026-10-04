// Mostafa Eldesouky


#include "UI/UserWidgets/TextWithNums/TextWithNumsWidget.h"

#include "Components/TextBlock.h"
#include "Statics/AuraSubSystem.h"

void UTextWithNumsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	AttributeName->SetText(FText::FromString(Attribute));
	UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.AddLambda([this](FString attributeName, int8 attributeAmount)
	{
		if (attributeName == Attribute)
			AttributeAmount->SetText(FText::FromString(FString::Printf(TEXT("%i"), attributeAmount)));
	});
}
