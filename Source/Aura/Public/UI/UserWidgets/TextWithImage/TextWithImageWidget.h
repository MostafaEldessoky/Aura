// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "TextWithImageWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class AURA_API UTextWithImageWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag GameplayTags;
	UPROPERTY(meta=(BindWidget))
	UImage* MassageImage;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MassageText;
	FTimerHandle TimerHandle;
	void SetVisibilityAfterEvent();
};
