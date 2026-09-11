// Mostafa Eldesouky


#include "Animations/AnimBase.h"

void UAnimBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
}

void UAnimBase::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (Pawn.IsValid()) MovementSpeed = Pawn->GetVelocity().Size();
}    

