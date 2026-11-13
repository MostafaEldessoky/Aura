// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateSessionWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API UCreateSessionWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* CreateSessionButton;
	UFUNCTION()
	void OnCreateSessionButtonClicked();
};
