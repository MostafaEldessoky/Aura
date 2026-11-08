// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Continue.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API UContinue : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* LoadButton;
	UFUNCTION()
	void OnLoadButtonClicked();
};
