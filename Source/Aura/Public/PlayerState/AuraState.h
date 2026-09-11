// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/AttributeInterface.h"
#include "AuraState.generated.h"

class UAuraAttributes;
class UAuraASC;
/**
 * 
 */
UCLASS()
class AURA_API AAuraState : public APlayerState , public IAbilitySystemInterface , public IAttributeInterface
{
	GENERATED_BODY()
public:
	AAuraState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AuraASC;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAttributes> AuraAttributes;
};
