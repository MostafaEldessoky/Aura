// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionButton.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API UFindSessionButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* FindSessionButton;
	UFUNCTION()
	void OnFindSessionButtonClicked();
};
