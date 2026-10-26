// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
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
	UPROPERTY(EditAnywhere,Category=CPPVars)
	FGameplayAttribute Attribute;
	UPROPERTY(meta=(BindWidget))
	UButton* Button;
	UFUNCTION()
	void LevelUp();
};
