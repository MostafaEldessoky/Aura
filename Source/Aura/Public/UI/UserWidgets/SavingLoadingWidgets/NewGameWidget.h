// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewGameWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API UNewGameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(meta=(BindWidget))
	UButton* NewGame;
	UFUNCTION()
	void OnNewGameClicked();
	UPROPERTY(EditAnywhere,Category=CPPVars)
	TSoftObjectPtr<UWorld> Level;
};
