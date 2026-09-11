// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/AttributeInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class AURA_API ACharacterBase : public ACharacter, public IAbilitySystemInterface , public IAttributeInterface
{
	GENERATED_BODY()
public:
	ACharacterBase();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
protected:
	UPROPERTY(VisibleAnywhere,Category="CPPVars")
	USkeletalMeshComponent* WeaponMesh;
};
