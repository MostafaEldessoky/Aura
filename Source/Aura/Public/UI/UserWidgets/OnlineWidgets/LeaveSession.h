// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaveSession.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class AURA_API ULeaveSession : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UButton* LeaveSessionButton;
	UFUNCTION()
	void OnLeaveSessionButtonClicked();
};
