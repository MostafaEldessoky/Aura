// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/HUDInterface.h"
#include "AuraHUD.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD , public IHUDInterface
{
	GENERATED_BODY()
public:
	virtual bool IsUserWidgetValid() override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BaseUserWidgetClass;
	TWeakObjectPtr<UUserWidget> BaseUserWidget{nullptr};
};
