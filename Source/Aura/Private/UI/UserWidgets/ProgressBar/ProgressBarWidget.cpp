// Mostafa Eldesouky


#include "UI/UserWidgets/ProgressBar/ProgressBarWidget.h"
#include "Components/ProgressBar.h"
#include "Statics/AuraSubSystem.h"

void UProgressBarWidget::SetActorName(FString Name) 
{
	ActorName = Name;
}
void UProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Attribute == "Health")
		MaxAttribute = "MaxHealth";
	else if (Attribute == "Mana")
		MaxAttribute = "MaxMana";
	ProgressBar->SetPercent(1.0f);
	if (bForWidgetComp)
		UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.AddLambda([this](FString ActorID,FString attributeName, float attributeAmount)
		{
			if (ActorName == ActorID)
			{
				if (attributeName == MaxAttribute)
					MaxAttributeAmount = attributeAmount;
				else if (attributeName == Attribute)
					ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
			}
		});
	else 
		UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.AddLambda([this](FString attributeName, float attributeAmount)
		{
			if (attributeName == MaxAttribute)
				MaxAttributeAmount = attributeAmount;
			else if (attributeName == Attribute)
				ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
		});
}
