// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ProgressBarInterface.h"
#include "ProgressBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class AURA_API UProgressBarWidget : public UUserWidget, public IProgressBarInterface
{
	GENERATED_BODY()
public:
	virtual void SetActorName(FString Name)  override;
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	bool bForWidgetComp{false};
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FString Attribute;
	FString MaxAttribute;
	float MaxAttributeAmount{1};
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	FString ActorName;
};
