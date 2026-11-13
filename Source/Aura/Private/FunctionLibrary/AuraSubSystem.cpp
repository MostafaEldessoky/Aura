// Mostafa Eldesouky


#include "Statics/AuraSubSystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "GameMode/AuraSaveGameSlotData.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"


UAuraSubSystem* UAuraSubSystem::GetAuraSubSystem(const UObject* WorldContextObject)
{
	auto AuraSubSystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UAuraSubSystem>();
	if (!AuraSubSystem->AuraData)
		AuraSubSystem->AuraData = Cast<UAuraData>(StaticLoadObject(UAuraData::StaticClass(), nullptr,
			TEXT("/Game/BluePrints/Data/BP_SharedData.BP_SharedData")));
	return AuraSubSystem;
}

void UAuraSubSystem::OpenMap(TSoftObjectPtr<UWorld> Level)
{
	OnInputPressed.Clear();
	OnInputReleased.Clear();
	OnPickedUpEffectItem.Clear();
	OnAttributeChangedPlayer.Clear();
	OnAttributeChangedForWidgetComp.Clear();
	OnNeedLevelUpAttribute.Clear();
	OnCooldownStart.Clear();
	OnGiveAbility.Clear();
	OnUnlockAbility.Clear();
	OnNeedLevelUpAbility.Clear();
	OnAssignAbilityToInput.Clear();
	OnToggleAttributeWidget.Clear();
	OnToggleSpellTreeWidget.Clear();
	OnToggleInGameMenuWidget.Clear();
	OnToggleSaveWidget.Clear();
	OnToggleLoadWidget.Clear();
	OnSaveGameNeeded.Clear();
	CurrentLevel = Level;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, CurrentLevel);
}

void UAuraSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (UGameplayStatics::DoesSaveGameExist("DEFAULT",0))
		AuraSaveGameSlotData = Cast<UAuraSaveGameSlotData>(UGameplayStatics::LoadGameFromSlot("DEFAULT",0));
	OnSaveGameToSlotNeeded.AddLambda([this](FString SlotName,int32 SlotIndex)
	{
		if (SlotName != "CONTINUE")
		{
			if (UGameplayStatics::DoesSaveGameExist("DEFAULT",0))
			{
				AuraSaveGameSlotData->MarkAsGarbage();
				AuraSaveGameSlotData = nullptr;
				AuraSaveGameSlotData = Cast<UAuraSaveGameSlotData>(UGameplayStatics::LoadGameFromSlot("DEFAULT",0));
				if (!AuraSaveGameSlotData->SlotData.Contains(SlotName))
				{
					AuraSaveGameSlotData->SlotData.Add(SlotName,SlotIndex);
					UGameplayStatics::SaveGameToSlot(AuraSaveGameSlotData,"DEFAULT",0);
				}
				else
				{
					if (UGameplayStatics::DoesSaveGameExist(SlotName,SlotIndex))
						UGameplayStatics::DeleteGameInSlot(SlotName,SlotIndex);
				}
			}
			else
			{
				AuraSaveGameSlotData = NewObject<UAuraSaveGameSlotData>();
				AuraSaveGameSlotData->SlotData.Add(SlotName,SlotIndex);
				UGameplayStatics::SaveGameToSlot(AuraSaveGameSlotData,"DEFAULT",0);
			}
		}
		if (AuraSaveGame) AuraSaveGame->MarkAsGarbage();
		AuraSaveGame = nullptr;
		TArray<FSaveGameBase> SaveGameArray;
		OnSaveGameNeeded.Broadcast(SaveGameArray);
		AuraSaveGame = NewObject<UAuraSaveGame>();
		AuraSaveGame->Level = CurrentLevel;
		AuraSaveGame->ObjectData = SaveGameArray;
		UGameplayStatics::SaveGameToSlot(AuraSaveGame,SlotName,SlotIndex);
		AuraSaveGame->MarkAsGarbage();
		AuraSaveGame = nullptr;
	});
	OnLoadGameSlotSelected.AddLambda([this](FString SlotName,int32 SlotIndex)
	{
		if (AuraSaveGame) AuraSaveGame->MarkAsGarbage();
		AuraSaveGame = nullptr;
		if (UGameplayStatics::DoesSaveGameExist(SlotName,SlotIndex))
		{
			AuraSaveGame = Cast<UAuraSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,SlotIndex));
			OpenMap(AuraSaveGame->Level);
		}
	});
	OnLoadGameSlotDeleted.AddLambda([this](FString SlotName,int32 SlotIndex)
	{
		if (UGameplayStatics::DoesSaveGameExist(SlotName,SlotIndex))
			UGameplayStatics::DeleteGameInSlot(SlotName,SlotIndex);
		if (UGameplayStatics::DoesSaveGameExist("DEFAULT",0))
		{
			AuraSaveGameSlotData->MarkAsGarbage();
			AuraSaveGameSlotData = nullptr;
			AuraSaveGameSlotData = Cast<UAuraSaveGameSlotData>(UGameplayStatics::LoadGameFromSlot("DEFAULT",0));
			AuraSaveGameSlotData->SlotData.Remove(SlotName);
			UGameplayStatics::SaveGameToSlot(AuraSaveGameSlotData,"DEFAULT",0);
		}
	});
}

void UAuraSubSystem::OnlineCreateSession()
{
	if (IOnlineSubsystem::Get()->GetSessionInterface()->GetNamedSession(NAME_GameSession))
		return;
	FDelegateHandle temp;
	OnCreateSessionCompleteDelegate.BindLambda([this,&temp](FName SessionName, bool bWasSuccessful)
	{
		// can implement players slots to be completed then travel to game map 
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(temp);
	});
	temp = IOnlineSubsystem::Get()->GetSessionInterface()->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? false : true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bAllowJoinInProgress = false;
	SessionSettings.NumPublicConnections = 6;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.Set(FName("GameType"),FString("Team"),EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	if (!IOnlineSubsystem::Get()->GetSessionInterface()->CreateSession(*GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId(),NAME_GameSession,SessionSettings))
	{
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(temp);
	}
}

void UAuraSubSystem::OnlineFindSession()
{
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch = MakeShared<FOnlineSessionSearch>();
	OnlineSessionSearch->MaxSearchResults = 10000;
	OnlineSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? false : true;
	OnlineSessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	FDelegateHandle temp;
	OnFindSessionsCompleteDelegate.BindLambda([this,&temp,OnlineSessionSearch](bool bWasSuccessful)
	{
		for (auto& temp1 : OnlineSessionSearch->SearchResults)
		{
			FString SearchString;
			temp1.Session.SessionSettings.Get(FName("GameType"),SearchString);
			if (SearchString == FString("Team"))
				OnListOfSessions.Broadcast(temp1);
		}
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnFindSessionsCompleteDelegate_Handle(temp);
	});
	temp = IOnlineSubsystem::Get()->GetSessionInterface()->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
	if (!IOnlineSubsystem::Get()->GetSessionInterface()->FindSessions(*GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId(),OnlineSessionSearch.ToSharedRef()))
	{
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnFindSessionsCompleteDelegate_Handle(temp);
	}
}

void UAuraSubSystem::OnlineJoinSession(FOnlineSessionSearchResult SessionResult)
{
	FDelegateHandle temp;
	OnJoinSessionCompleteDelegate.BindLambda([this,&temp]( FName SessionName, EOnJoinSessionCompleteResult::Type Result )
	{
		FString ConnectString;
		IOnlineSubsystem::Get()->GetSessionInterface()->GetResolvedConnectString(SessionName,ConnectString);
		GetGameInstance()->GetFirstLocalPlayerController()->ClientTravel(ConnectString,TRAVEL_Absolute);
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnJoinSessionCompleteDelegate_Handle(temp);
	});
	temp = IOnlineSubsystem::Get()->GetSessionInterface()->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
	if (!IOnlineSubsystem::Get()->GetSessionInterface()->JoinSession(*GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId(),NAME_GameSession,SessionResult))
	{
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnJoinSessionCompleteDelegate_Handle(temp);
	}
}

void UAuraSubSystem::OnlineStartSession(FString Map)
{
	FDelegateHandle temp;
	OnStartSessionCompleteDelegate.BindLambda([this,&temp,Map]( FName SessionName, bool bWasSuccessful )
	{
		GetWorld()->ServerTravel(Map,true);
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnStartSessionCompleteDelegate_Handle(temp);
	});
	temp = IOnlineSubsystem::Get()->GetSessionInterface()->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
	if (!IOnlineSubsystem::Get()->GetSessionInterface()->StartSession(NAME_GameSession))
	{
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnStartSessionCompleteDelegate_Handle(temp);
	}
}

void UAuraSubSystem::OnlineDestroySession()
{
	FDelegateHandle temp;
	OnDestroySessionCompleteDelegate.BindLambda([this,&temp]( FName SessionName, bool bWasSuccessful )
	{
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnDestroySessionCompleteDelegate_Handle(temp);
	});
	temp = IOnlineSubsystem::Get()->GetSessionInterface()->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
	if (!IOnlineSubsystem::Get()->GetSessionInterface()->DestroySession(NAME_GameSession,OnDestroySessionCompleteDelegate))
	{
		IOnlineSubsystem::Get()->GetSessionInterface()->ClearOnDestroySessionCompleteDelegate_Handle(temp);
	}
}
