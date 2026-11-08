// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "LoadWidget.generated.h"

class UAuraSaveGameSlotData;
class UScrollBox;
class UTextBlock;
class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class AURA_API ULoadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FString SlotName;
	bool bIsReady{false};
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* SlotData;
	UPROPERTY(Meta = (BindWidget))
	UButton* LoadButton;
	UPROPERTY(Meta = (BindWidget))
	UButton* DeleteButton;
	UFUNCTION()
	void OnLoadButtonClicked();
	UFUNCTION()
	void OnDeleteButtonClicked();
	void CallUntilReady(); 
};
