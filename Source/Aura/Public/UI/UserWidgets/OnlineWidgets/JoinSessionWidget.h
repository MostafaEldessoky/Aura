// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "JoinSessionWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class AURA_API UJoinSessionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	 FOnlineSessionSearchResult SessionSearchResult;
	bool bIsReady{false};
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* SessionID;
	UPROPERTY(Meta = (BindWidget))
	UButton* JoinSessionButton;
	UFUNCTION()
	void OnJoinSessionButtonClicked();
	void CallUntilReady();
};
