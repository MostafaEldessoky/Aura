// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadButton.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API ULoadButton : public UUserWidget
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
