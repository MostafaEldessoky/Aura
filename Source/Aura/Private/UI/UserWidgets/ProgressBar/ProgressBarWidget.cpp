// Mostafa Eldesouky


#include "UI/UserWidgets/ProgressBar/ProgressBarWidget.h"

#include "Components/ProgressBar.h"
#include "Statics/Utilities.h"

void UProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Attribute == "Health")
		MaxAttribute = "MaxHealth";
	else if (Attribute == "Mana")
		MaxAttribute = "MaxMana";
	ProgressBar->SetPercent(1.0f);
	UUtilities::GetAuraSubSystem(this)->OnAttributeChangedSelf.AddLambda([this](FString attributeName, float attributeAmount)
	{
		if (attributeName == MaxAttribute)
			MaxAttributeAmount = attributeAmount;
		else if (attributeName == Attribute)
			ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
	});
}
