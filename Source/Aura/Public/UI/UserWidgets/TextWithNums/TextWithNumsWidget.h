// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextWithNumsWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class AURA_API UTextWithNumsWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FString Attribute;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AttributeName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AttributeAmount;
};
