// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAnimBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
protected:
	UPROPERTY(BlueprintReadOnly,Category="CPPVars")
	float MovementSpeed;
	UPROPERTY(BlueprintReadOnly,Category="CPPVars")
	UBlendSpace* MovementBlendSpace;
private:
	TWeakObjectPtr<APawn> Pawn;
};
