// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "Interfaces/Targetable.h"
#include "AuraEnemyBase.generated.h"

class UAuraAttributes;
class UAuraASC;

UCLASS()
class AURA_API AAuraEnemyBase : public ACharacterBase , public ITargetable
{
	GENERATED_BODY()

public:
	AAuraEnemyBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
	virtual void Highlight() override;
	virtual void UnHighlight() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraASC> AuraASC;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAttributes> AuraAttributes;
	
};
