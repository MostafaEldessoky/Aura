// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "AuraEnemyBase.generated.h"

class UWidgetComponent;
class UAuraAttributes;
class UAuraASC;

UCLASS()
class AURA_API AAuraEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AAuraEnemyBase();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributes* GetAuraAttributes() const override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraASC> AuraASC;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAttributes> AuraAttributes;
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;
};
