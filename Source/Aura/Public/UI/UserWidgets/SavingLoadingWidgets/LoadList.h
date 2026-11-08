// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadList.generated.h"

class ULoadWidget;
class UAuraSaveGameSlotData;
class UScrollBox;
/**
 * 
 */
UCLASS()
class AURA_API ULoadList : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	bool bShow{false};
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* ScrollBox;
	UPROPERTY(EditAnywhere,Category="CPPVars")
	TSubclassOf<ULoadWidget> LoadWidgetClass;
	UPROPERTY()
	UAuraSaveGameSlotData* SaveGameSlotData{nullptr};
	UPROPERTY()
	TArray<ULoadWidget*> LoadWidgets;
	UPROPERTY()
	TArray<UPanelSlot*> LoadWidgetSlots;
};
