// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "Combat.generated.h"

class UWidgetComponent;
class UCapsuleComponent;
class USphereComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeath,AActor*)

// This class does not need to be modified.
UINTERFACE()
class UCombat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombat
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Highlight() = 0;
	virtual void UnHighlight() = 0;
	virtual UCapsuleComponent* GetCapsule() = 0;
	virtual USkeletalMeshComponent* GetModelMesh() = 0;
	virtual USkeletalMeshComponent* GetWeaponMesh() = 0;
	virtual FTransform GetWeaponMechanicSocketTransform() = 0;
	virtual void TargetMotionWarping(FVector TargetLocation) = 0;
	virtual FGameplayTag GetCharacterID() = 0;
	virtual FOnDeath& GetOnDeathDelegate() = 0;
	virtual UDecalComponent* GetDecalComponent() = 0;
	virtual bool IsWidgetComponentValid() = 0;
	virtual UWidgetComponent* GetWidgetComponent() = 0;
};
