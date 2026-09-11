// Mostafa Eldesouky

#pragma once

#include <Functional>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraSubSystem.h"
#include "Utilities.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API UUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void Initialize(const UObject* WorldContextObject,std::function<bool()> FuncToCheck, std::function<void()> FuncToCall);
	static UAuraSubSystem* GetAuraSubSystem(const UObject* WorldContextObject);

};
