// Mostafa Eldesouky


#include "UI/UserWidgets/TextWithImage/TextWithImageWidget.h"
#include "AbilitySystemComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"


void UTextWithImageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetVisibility(ESlateVisibility::Collapsed);
	for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIData)
		if (MassageTag.MatchesTagExact(temp.MassageTag))
		{
			MassageImage->Brush.SetResourceObject(temp.MassageImage);
			MassageText->SetText(temp.MassageText);
		}
	UAuraSubSystem::GetAuraSubSystem(this)->OnPickedUpEffectItem.AddLambda(
		[this](FGameplayTagContainer TagContainer)
		{
			if (TagContainer.HasTagExact(MassageTag))
			{
				SetVisibility(ESlateVisibility::Visible);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTextWithImageWidget::SetVisibilityAfterEvent, 2.0f, false);
			}
		});
}
void UTextWithImageWidget::SetVisibilityAfterEvent()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
