// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/AttributeInterface.h"
#include "Interfaces/Combat.h"
#include "CharacterBase.generated.h"

class UMotionWarpingComponent;

UCLASS()
class AURA_API ACharacterBase : public ACharacter, public IAbilitySystemInterface , public IAttributeInterface, public ICombat
{
	GENERATED_BODY()
public:
	ACharacterBase();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
	virtual FTransform GetWeaponSocketTransform() override;
	virtual void TargetMotionWarping(FVector TargetLocation) override;
protected:
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	UMotionWarpingComponent* MotionWarpingComponent;
};
