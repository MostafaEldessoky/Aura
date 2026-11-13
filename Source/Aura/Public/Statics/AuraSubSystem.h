// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameMode/AuraSaveGame.h"
#include "Interfaces/OnlineGameMatchesInterface.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AuraSubSystem.generated.h"


class ITargetable;
class UAuraData;
class UAuraSaveGameSlotData;

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
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLoadGameSlotSelected,FString,int32)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSaveGameToSlotNeeded,FString,int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameNeeded,TArray<FSaveGameBase>&)
DECLARE_MULTICAST_DELEGATE(FOnLoadGameNeeded)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListOfSessions,FOnlineSessionSearchResult)


/**
 * 
 */
UCLASS()
class AURA_API UAuraSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UAuraSubSystem* GetAuraSubSystem(const UObject* WorldContextObject);
	UFUNCTION()
	void OpenMap(TSoftObjectPtr<UWorld> World);
	TSoftObjectPtr<UWorld> CurrentLevel{nullptr};
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UPROPERTY()
	UAuraData* AuraData{nullptr};
	UPROPERTY()
	UAuraSaveGame* AuraSaveGame{nullptr};
	UPROPERTY()
	UAuraSaveGameSlotData* AuraSaveGameSlotData{nullptr};
	void OnlineCreateSession();
	void OnlineFindSession();
	void OnlineJoinSession(FOnlineSessionSearchResult SessionResult);
	void OnlineStartSession(FString Map);
	void OnlineDestroySession();
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
	FOnToggleWidget OnToggleInGameMenuWidget;
	FOnToggleWidget OnToggleSaveWidget;
	FOnToggleWidget OnToggleLoadWidget;
	FOnToggleWidget OnToggleFindSessionWidget;
	FOnLoadGameSlotSelected OnLoadGameSlotSelected;
	FOnLoadGameSlotSelected OnLoadGameSlotDeleted;
	FOnSaveGameToSlotNeeded OnSaveGameToSlotNeeded;
	FOnSaveGameNeeded OnSaveGameNeeded;
	FOnLoadGameNeeded OnLoadGameNeeded;
	FOnListOfSessions OnListOfSessions;
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
};
