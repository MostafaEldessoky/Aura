// Mostafa Eldesouky


#include "UI/UserWidgets/TextWithImage/TextWithImageWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/Utilities.h"


void UTextWithImageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetVisibility(ESlateVisibility::Collapsed);
	for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->MassageData)
		if (GameplayTags.MatchesTagExact(temp.MassageTag))
		{
			MassageImage->Brush.SetResourceObject(temp.MassageImage);
			MassageText->SetText(temp.MassageText);
		}
	UUtilities::GetAuraSubSystem(this)->OnPickedUpEffectItem.AddLambda(
		[this](FGameplayTagContainer TagContainer)
		{
			if (TagContainer.HasTagExact(GameplayTags))
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
