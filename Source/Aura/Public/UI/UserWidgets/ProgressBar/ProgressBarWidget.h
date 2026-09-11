// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class AURA_API UProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FString Attribute;
	FString MaxAttribute;
	float MaxAttributeAmount{1};
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
};
