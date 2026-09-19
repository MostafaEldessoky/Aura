// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraController.generated.h"

class UAuraData;
class UUtilities;
class ITargetable;
/**
 * 
 */
UCLASS()
class AURA_API AAuraController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	void TraceUnderMouse();
	TScriptInterface<ITargetable> CurrentTarget{nullptr};
	TScriptInterface<ITargetable> LastTarget{nullptr};
};
