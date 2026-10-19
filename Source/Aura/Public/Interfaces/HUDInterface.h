// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsUserWidgetValid() = 0;
};
