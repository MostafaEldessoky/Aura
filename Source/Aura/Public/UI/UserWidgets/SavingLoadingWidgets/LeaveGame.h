// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaveGame.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API ULeaveGame : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* LeaveGameButton;
	UFUNCTION()
	void OnLeaveGameButtonClicked();
};
