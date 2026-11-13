// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionList.generated.h"

class UJoinSessionWidget;
class UScrollBox;
/**
 * 
 */
UCLASS()
class AURA_API UFindSessionList : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	bool bShow{false};
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* ScrollBox;
	UPROPERTY(EditAnywhere,Category="CPPVars")
	TSubclassOf<UJoinSessionWidget> JoinSessionWidgetClass;
	UPROPERTY()
	TArray<UJoinSessionWidget*> JoinSessionWidgets;
};
