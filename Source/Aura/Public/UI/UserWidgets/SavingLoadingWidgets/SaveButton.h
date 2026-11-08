// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveButton.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API USaveButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* SaveButton;
	UFUNCTION()
	void OnSaveButtonClicked();
};
