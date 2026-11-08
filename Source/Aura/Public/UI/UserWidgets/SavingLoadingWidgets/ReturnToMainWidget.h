// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReturnToMainWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API UReturnToMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* SaveButton;
	UFUNCTION()
	void OnSaveButtonClicked();
	UPROPERTY(EditAnywhere,Category=CPPVars)
	TSoftObjectPtr<UWorld> Level;
};
