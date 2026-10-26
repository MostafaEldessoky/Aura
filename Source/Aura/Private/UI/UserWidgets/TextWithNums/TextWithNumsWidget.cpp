// Mostafa Eldesouky


#include "UI/UserWidgets/TextWithNums/TextWithNumsWidget.h"

#include "Components/TextBlock.h"
#include "Statics/AuraSubSystem.h"
#include "Logging/LogMacros.h"

void UTextWithNumsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	AttributeName->SetText(FText::FromString(Attribute.GetName()));
	UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.AddLambda([this](FString attributeName, float attributeAmount)
	{
		if (attributeName == Attribute.GetName())
		{
			if (AttributeAmount)
				AttributeAmount->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), attributeAmount)));
		}
	});
}
