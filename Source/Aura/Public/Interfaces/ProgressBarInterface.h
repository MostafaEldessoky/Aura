// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProgressBarInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UProgressBarInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IProgressBarInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetActorName(FString Name) = 0;
};
