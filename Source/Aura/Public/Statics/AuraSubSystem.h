// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AuraSubSystem.generated.h"

class ITargetable;
class UAuraData;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputPressed,FGameplayTag)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputReleased,FGameplayTag)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickedUpEffectItem, FGameplayTagContainer)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedPlayer,const FString&,float)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedEnemy,FString,const FString&,float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNeedLevelUpAttribute,const FString&)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCooldownBegain,FGameplayTag,float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnlockAbility,FGameplayTag)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGiveAbility,FGameplayTagContainer)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNeedLevelUpAbility,FGameplayTag)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssignAbilityToInput,FGameplayTagContainer)
DECLARE_MULTICAST_DELEGATE(FOnToggleWidget)

/**
 * 
 */
UCLASS()
class AURA_API UAuraSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UAuraSubSystem* GetAuraSubSystem(const UObject* WorldContextObject);
	UPROPERTY()
	UAuraData* AuraData{nullptr};
	FOnInputPressed OnInputPressed;
	FOnInputReleased OnInputReleased;
    FOnPickedUpEffectItem OnPickedUpEffectItem;
    FOnAttributeChangedPlayer OnAttributeChangedPlayer;
    FOnAttributeChangedEnemy OnAttributeChangedForWidgetComp;
    FOnNeedLevelUpAttribute OnNeedLevelUpAttribute;
	FOnCooldownBegain OnCooldownStart;
	FOnGiveAbility OnGiveAbility;
	FOnUnlockAbility OnUnlockAbility;
	FOnNeedLevelUpAbility OnNeedLevelUpAbility;
	FOnAssignAbilityToInput OnAssignAbilityToInput;
	FOnToggleWidget OnToggleAttributeWidget;
	FOnToggleWidget OnToggleSpellTreeWidget;
};
