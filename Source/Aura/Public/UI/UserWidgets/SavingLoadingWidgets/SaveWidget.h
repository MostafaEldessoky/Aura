// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveWidget.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class AURA_API USaveWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	bool bShow{false};
	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* SlotName;
	UPROPERTY(Meta = (BindWidget))
	UButton* SaveButton;
	FString SlotNameText;
	UFUNCTION()
	void OnSlotNameTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnSaveButtonClicked();
};
