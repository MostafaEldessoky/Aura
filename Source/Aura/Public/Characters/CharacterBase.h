// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
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
	virtual void Highlight() override;
	virtual void UnHighlight() override;
	virtual UCapsuleComponent* GetCapsule() override;
	virtual USkeletalMeshComponent* GetModelMesh() override;
	virtual USkeletalMeshComponent* GetWeaponMesh() override;
	virtual FTransform GetWeaponMechanicSocketTransform() override;
	virtual void TargetMotionWarping(FVector TargetLocation) override;
	virtual FGameplayTag GetCharacterID() override;
	virtual FOnDeath& GetOnDeathDelegate() override;
	virtual UDecalComponent* GetDecalComponent() override;
protected:
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	UMotionWarpingComponent* MotionWarpingComponent;
	FOnDeath OnDeathDelegate;
private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CharacterTagID;
};
