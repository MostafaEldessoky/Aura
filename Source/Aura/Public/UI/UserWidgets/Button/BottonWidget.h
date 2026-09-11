// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BottonWidget.generated.h"

class UButton;

UCLASS()
class AURA_API UBottonWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(meta=(BindWidget))
	UButton* Button;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FString Attribute;
	UFUNCTION()
	void LevelUp();
};
