// Mostafa Eldesouky


#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "PlayerState/AuraState.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/AuraFunctionLibrary.h"

UAuraASC::UAuraASC()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}
void UAuraASC::Client_BroadCastPickUpItem_Implementation(const FGameplayTagContainer& TagContainer)
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnPickedUpEffectItem.Broadcast(TagContainer);
}
void UAuraASC::BeginPlay()
{
	Super::BeginPlay();
	OnGameplayEffectAppliedDelegateToSelf.AddLambda( [this](UAbilitySystemComponent* ASC, 
    	                                                        const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
    	{
    		FGameplayTagContainer TagContainer;
    		SpecApplied.GetAllAssetTags(TagContainer);
    		if (TagContainer.HasTag(Aura::UI::PickUp))
    			Client_BroadCastPickUpItem(TagContainer);
    	});
	AuraAttributes = Cast<IAttributeInterface>(GetOwner())->GetAuraAttributes();
	if (Cast<APlayerState>(GetOwner())) // Player State
		UAuraFunctionLibrary::TickFuncUntil(this,[this](){return Cast<APlayerState>(GetOwner())->GetPawn() != nullptr;},
		[this]()
		{
			SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
			InitAbilityActorInfo(GetOwner(),Cast<APlayerState>(GetOwner())->GetPawn());
			CombatCharacter = GetAvatarActor();
			InitializeAbilities(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartUpAbilities);
			PlayerBroadcastAttributeChange();
			PlayerLevelUp();
			PlayerInputs();
			OnDeath();
			GetWorld()->GetTimerManager().SetTimer(InitializeStartupAttributesTimerHandle,this,&UAuraASC::PlayerInitializeStartupAttributes,0.5f,false);
		});
	else // Enemy Pawn
		UAuraFunctionLibrary::TickFuncUntil(this,[this](){return GetOwner() != nullptr;},
		[this]()
		{
			SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
			InitAbilityActorInfo(GetOwner(),GetOwner());
			CombatCharacter = GetAvatarActor();
			InitializeAbilities(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartUpAbilities);
			EnemyBroadcastAttributeChange();
			OnDeath();
			GetWorld()->GetTimerManager().SetTimer(InitializeStartupAttributesTimerHandle,this,&UAuraASC::EnemyInitializeStartupAttributes,0.5f,false);
		});
}
void UAuraASC::PlayerBroadcastAttributeChange()
{
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
		for (const auto& temp : AuraAttributes->FuncPointers)
			GetGameplayAttributeValueChangeDelegate(temp()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.Broadcast(Data.Attribute.GetName(),Data.Attribute.GetNumericValue(AuraAttributes.Get()));
			});
}
void UAuraASC::PlayerLevelUp()
{
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
		UAuraSubSystem::GetAuraSubSystem(this)->OnNeedLevelUpAttribute.AddLambda([this](const FString& AttributeName)
		{
			Server_ApplyLevelUpEffect(AttributeName);
		});
}
void UAuraASC::Server_ApplyLevelUpEffect_Implementation(const FString& AttributeName)
{
	const auto InputTag = UAuraFunctionLibrary::MakeAttributeTagFromName(AttributeName);
	auto temp = Cast<IAttributeInterface>(GetAvatarActor())->GetAuraAttributes();
	if (temp->GetXP() >= temp->GetMaxXP())
		ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[InputTag],
			1,MakeEffectContext()).Data.Get());
}
void UAuraASC::PlayerInitializeStartupAttributes()
{
	if (Cast<APawn>(GetAvatarActor())->HasAuthority())
		for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartupAttributes)
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[temp],1,MakeEffectContext()).Data.Get());
}
void UAuraASC::EnemyBroadcastAttributeChange()
{
	for (const auto& temp : AuraAttributes->FuncPointers)
		GetGameplayAttributeValueChangeDelegate(temp()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			if (AuraAttributes->GetHealthAttribute() == Data.Attribute || AuraAttributes->GetMaxHealthAttribute() == Data.Attribute || AuraAttributes->GetManaAttribute() == Data.Attribute || AuraAttributes->GetMaxManaAttribute() == Data.Attribute)
				UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedEnemy.Broadcast(GetAvatarActor()->GetName(),Data.Attribute.GetName(),Data.Attribute.GetNumericValue(AuraAttributes.Get()));
		});
}
void UAuraASC::EnemyInitializeStartupAttributes()
{
	if (Cast<APawn>(GetOwner())->HasAuthority()) 
		for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartupAttributes)
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[temp],1,MakeEffectContext()).Data.Get());
}
void UAuraASC::InitializeAbilities(TArray<FGameplayTag> AbilitiesTags)
{
	if (Cast<APawn>(GetAvatarActor())->HasAuthority())
	{
		for (const auto& temp : AbilitiesTags)
			GiveAbility(FGameplayAbilitySpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->AbilitiesClasses[temp].AbilityClass));
	}
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
	{
		TryActivateAbilitiesByTag(Aura::Abilities::TraceUnderMouse.GetTag().GetSingleTagContainer());
		TryActivateAbilitiesByTag(Aura::Abilities::HighLight.GetTag().GetSingleTagContainer());
	}
}
void UAuraASC::OnDeath()
{
	CombatCharacter->GetOnDeathDelegate().AddLambda([this](AActor* Killer)
	{
		FGameplayEventData EventData;
		EventData.Target = Killer;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),Aura::Abilities::Death,EventData);
	});
}
void UAuraASC::PlayerInputs()
{
	if (!Cast<APawn>(GetAvatarActor())->IsLocallyControlled()) return;
	UAuraSubSystem::GetAuraSubSystem(this)->OnInputPressed.AddLambda([this](FGameplayTag Key)
	{
		FGameplayEventData EventData;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),Key,EventData);
	});
	UAuraSubSystem::GetAuraSubSystem(this)->OnInputReleased.AddLambda([this](FGameplayTag Key)
	{
		TArray<FGameplayAbilitySpec*> MatchingGameplayAbilities;
		GetActivatableGameplayAbilitySpecsByAllMatchingTags(Key.GetSingleTagContainer(),MatchingGameplayAbilities);
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,MatchingGameplayAbilities[0]->Handle,
			MatchingGameplayAbilities[0]->GetPrimaryInstance()->GetCurrentActivationInfo().GetActivationPredictionKey());
	});
}
