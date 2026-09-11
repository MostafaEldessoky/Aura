// Mostafa Eldesouky


#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "PlayerState/AuraState.h"
#include "Data/Tags.h"
#include "Interfaces/Targetable.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/Utilities.h"

UAuraASC::UAuraASC()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}
void UAuraASC::Client_BroadCastPickUpItem_Implementation(const FGameplayEffectSpec& SpecApplied)
{
	FGameplayTagContainer TagContainer;
	SpecApplied.GetAllAssetTags(TagContainer);
	if (TagContainer.HasTag(Tags::UIMassage::UIMassage))
		UUtilities::GetAuraSubSystem(this)->OnPickedUpEffectItem.Broadcast(TagContainer);
}
void UAuraASC::BeginPlay()
{
	Super::BeginPlay();
	OnGameplayEffectAppliedDelegateToSelf.AddLambda( [this](UAbilitySystemComponent* ASC, 
		const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
     {
        Client_BroadCastPickUpItem(SpecApplied);
     });
	AuraAttributes = Cast<IAttributeInterface>(GetOwner())->GetAuraAttributes();
	if (Cast<APlayerState>(GetOwner())) // Player State
		UUtilities::Initialize(this,[this](){return Cast<APlayerState>(GetOwner())->GetPawn() != nullptr;},
		[this]()
		{
			SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
			InitAbilityActorInfo(GetOwner(),Cast<APlayerState>(GetOwner())->GetPawn());
			InitializePlayerAbilities();
			PlayerBroadcastAttributeChange();
			PlayerLevelUp();
			PlayerListenToInputEvents();
			GetWorld()->GetTimerManager().SetTimer(InitializeStartupAttributesTimerHandle,this,&UAuraASC::PlayerInitializeStartupAttributes,0.1f,false);
		});
	else // Enemy Pawn
		UUtilities::Initialize(this,[this](){return GetOwner() != nullptr;},
		[this]()
		{
			SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
			InitAbilityActorInfo(GetOwner(),GetOwner());
			InitializeEnemyAbilities();
			EnemyBroadcastAttributeChange();
			GetWorld()->GetTimerManager().SetTimer(InitializeStartupAttributesTimerHandle,this,&UAuraASC::EnemyInitializeStartupAttributes,0.1f,false);
		});
}
void UAuraASC::PlayerBroadcastAttributeChange()
{
	if (Cast<APlayerState>(GetOwner())->GetPawn()->IsLocallyControlled())
		for (const auto& temp : AuraAttributes->FuncPtrs)
			GetGameplayAttributeValueChangeDelegate(temp()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				UUtilities::GetAuraSubSystem(this)->OnAttributeChangedSelf.Broadcast(Data.Attribute.GetName(),Data.Attribute.GetNumericValue(AuraAttributes.Get()));
			});
}
void UAuraASC::PlayerLevelUp()
{
	if (Cast<APlayerState>(GetOwner())->GetPawn()->IsLocallyControlled())
		UUtilities::GetAuraSubSystem(this)->OnNeedLevelUpAttribute.AddLambda([this](const FString& AttributeName)
		{
			Server_ApplyLevelUpEffect(AttributeName);
		});
}
void UAuraASC::Server_ApplyLevelUpEffect_Implementation(const FString& AttributeName)
{
	// if (UUtilities::PointLevel <= 0) return; // need way to authrize level up upon requist
	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);
	for (const auto& temp : Attributes)
	{
		if (temp.GetName() == AttributeName)
		{
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(
				UUtilities::GetAuraSubSystem(this)->AuraData->LevelUpData[temp.GetName()].EffectClass,
				UUtilities::GetAuraSubSystem(this)->AuraData->LevelUpData[temp.GetName()].EffectLevel,
				MakeEffectContext()).Data.Get());
			break;
		}
	}
}
void UAuraASC::PlayerInitializeStartupAttributes()
{
	if (Cast<APlayerState>(GetOwner())->GetPawn()->HasAuthority())
		for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.StartupAttributes)
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(temp,UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.EffectLevel,MakeEffectContext()).Data.Get());
}
void UAuraASC::EnemyBroadcastAttributeChange()
{
	for (const auto& temp : AuraAttributes->FuncPtrs)
		GetGameplayAttributeValueChangeDelegate(temp()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			if (AuraAttributes->GetHealthAttribute() == Data.Attribute || AuraAttributes->GetManaAttribute() == Data.Attribute)
				UUtilities::GetAuraSubSystem(this)->OnAttributeChangedEnemy.Broadcast(Data.Attribute);
		});
}
void UAuraASC::EnemyInitializeStartupAttributes()
{
	if (Cast<APawn>(GetOwner())->HasAuthority()) 
		for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.StartupAttributes)
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(temp,UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.EffectLevel,MakeEffectContext()).Data.Get());
}
void UAuraASC::InitializePlayerAbilities()
{
	for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->PlayerData.Abilities)
		GiveAbility(FGameplayAbilitySpec(temp));
}
void UAuraASC::InitializeEnemyAbilities()
{
	for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->EnemyData.Abilities)
		GiveAbility(FGameplayAbilitySpec(temp));
}
void UAuraASC::PlayerListenToInputEvents()
 {
 	UUtilities::GetAuraSubSystem(this)->OnInputPressed.AddLambda(
 		[this](FGameplayTag InputTag,FVector TargetLocation,TScriptInterface<ITargetable> TargetPawn)
 		{
 			FGameplayTagContainer GameplayTagContainer;
 			GameplayTagContainer.AddTag(InputTag);
 			TArray<FGameplayAbilitySpec*> MatchingGameplayAbilities;
 			GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer,MatchingGameplayAbilities);
 			for (const auto& temp : MatchingGameplayAbilities)
 				if (!temp->IsActive())
 				{
 					TryActivateAbility(temp->Handle);
 					// way to pass data to the ability
 				}
 		});
 }