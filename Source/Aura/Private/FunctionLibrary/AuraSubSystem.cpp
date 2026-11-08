// Mostafa Eldesouky


#include "Statics/AuraSubSystem.h"
#include "Data/AuraData.h"
#include "GameMode/AuraSaveGameSlotData.h"
#include "Kismet/GameplayStatics.h"

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
