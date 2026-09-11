// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AuraSubSystem.generated.h"

class ITargetable;
class UAuraData;
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputPressed,FGameplayTag,FVector,TScriptInterface<ITargetable>)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickedUpEffectItem, FGameplayTagContainer)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedSelf,const FString&,float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedEnemy,FGameplayAttribute)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNeedLevelUpAttribute,const FString&)
/**
 * 
 */
UCLASS()
class AURA_API UAuraSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UPROPERTY()
	const UAuraData* AuraData;
	FOnInputPressed OnInputPressed;
    FOnPickedUpEffectItem OnPickedUpEffectItem;
    FOnAttributeChangedSelf OnAttributeChangedSelf;
    FOnAttributeChangedEnemy OnAttributeChangedEnemy;
    FOnNeedLevelUpAttribute OnNeedLevelUpAttribute;
};
