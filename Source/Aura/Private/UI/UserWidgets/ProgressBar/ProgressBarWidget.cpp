// Mostafa Eldesouky


#include "UI/UserWidgets/ProgressBar/ProgressBarWidget.h"
#include "Components/ProgressBar.h"
#include "Statics/AuraSubSystem.h"

void UProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Attribute == "Health")
		MaxAttribute = "MaxHealth";
	else if (Attribute == "Mana")
		MaxAttribute = "MaxMana";
	ProgressBar->SetPercent(1.0f);
	if (bIsPlayer)
		UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.AddLambda([this](FString attributeName, float attributeAmount)
			{
				if (attributeName == MaxAttribute)
					MaxAttributeAmount = attributeAmount;
				else if (attributeName == Attribute)
					ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
			});
	else 
		UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedEnemy.AddLambda([this](FString EnemyId,FString attributeName, float attributeAmount)
			{
				if (EnemyName == EnemyId)
				{
					if (attributeName == MaxAttribute)
						MaxAttributeAmount = attributeAmount;
					else if (attributeName == Attribute)
						ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
				}
			});
}
