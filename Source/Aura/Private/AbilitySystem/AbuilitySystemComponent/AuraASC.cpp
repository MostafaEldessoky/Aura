// Mostafa Eldesouky

#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Data/AuraData.h"
#include "PlayerState/AuraState.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"
#include "Interfaces/HUDInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/AuraFunctionLibrary.h"
#include "GameFramework/HUD.h"

UAuraASC::UAuraASC()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}
void UAuraASC::BeginPlay()
{
	Super::BeginPlay();
	OnActiveGameplayEffectAddedDelegateToSelf.AddLambda([this](UAbilitySystemComponent* ASC, 
																const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
	{
		FGameplayTagContainer TagContainer;
		SpecApplied.GetAllGrantedTags(TagContainer);
		if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled() && TagContainer.HasTag(Aura::Cooldown::Cooldown))
			UAuraSubSystem::GetAuraSubSystem(this)->OnCooldownStart.Broadcast(TagContainer.First(),SpecApplied.Duration);
	});
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
			PlayerBroadcastAttributeChange();
			PlayerLevelUp();
			PlayerInputs();
			OnDeath();
			PlayerUnlockAbility();
			PlayerLevelUpAbility();
			PlayerChangeAbilityInputBinding();
			IsUIReadyForPlayerInitializeStartupAttributes();
			IsUIReadyForSSimulatedPlayersToInitializeStartupAttributes();
			PlayerSaveGame();
		});
	else // Enemy Pawn
		UAuraFunctionLibrary::TickFuncUntil(this,[this](){return GetOwner() != nullptr;},
		[this]()
		{
			SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
			InitAbilityActorInfo(GetOwner(),GetOwner());
			CombatCharacter = GetAvatarActor();
			InitializeAbilities(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartUpAbilities);
			BroadcastAttributeChangeForWidgetComp();
			OnDeath();
			IsUIReadyForEnemyInitializeStartupAttributes();
		});
}
void UAuraASC::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	if (!Cast<APlayerState>(GetOwner()) || !Cast<APawn>(GetAvatarActor())->IsLocallyControlled()) 
		return;
	
	if (AbilitySpec.Ability.Get()->GetAssetTags().First().MatchesTag(Aura::Abilities::Attack::Attack))
	{
		auto temp = UAuraSubSystem::GetAuraSubSystem(this)->AuraData->AbilitiesClasses[AbilitySpec.Ability.Get()->GetAssetTags().First()].AbilityInputTag;
		if (temp.IsValid()) AbilityInputBindings.Add(AbilitySpec.Ability.Get()->GetAssetTags().First(),temp);
		FGameplayTagContainer Container;
		Container.AddTag(AbilitySpec.Ability.Get()->GetAssetTags().First());
		auto temp1 = AbilityInputBindings.Find(AbilitySpec.Ability.Get()->GetAssetTags().First());
		if (temp1) Container.AddTag(*temp1);
		UAuraSubSystem::GetAuraSubSystem(this)->OnGiveAbility.Broadcast(Container);
	}
	if (AbilitySpec.Ability->GetAssetTags().HasTagExact(Aura::Abilities::TraceUnderMouse))
		TryActivateAbilitiesByTag(Aura::Abilities::TraceUnderMouse.GetTag().GetSingleTagContainer());
	if (AbilitySpec.Ability->GetAssetTags().HasTagExact(Aura::Abilities::HighLight))
		TryActivateAbilitiesByTag(Aura::Abilities::HighLight.GetTag().GetSingleTagContainer());
}
void UAuraASC::Client_BroadCastPickUpItem_Implementation(const FGameplayTagContainer& TagContainer)
{
	UAuraSubSystem::GetAuraSubSystem(this)->OnPickedUpEffectItem.Broadcast(TagContainer);
}
void UAuraASC::PlayerSaveGame()
{
	if (GetNetMode() == ENetMode::NM_Standalone )
		UAuraSubSystem::GetAuraSubSystem(this)->OnSaveGameNeeded.AddLambda([this](TArray<FSaveGameBase>& SaveGameArray)
		{
			FSaveGameBase PlayerSaveGame;
			PlayerSaveGame.ID = CombatCharacter->GetCharacterID();
			PlayerSaveGame.bIsDestroyed = false;
			PlayerSaveGame.Transform = GetAvatarActor()->GetTransform();
			PlayerSaveGame.CharacterSaveGame.Health = AuraAttributes->GetHealth();
			PlayerSaveGame.CharacterSaveGame.Mana = AuraAttributes->GetMana();
			PlayerSaveGame.PlayerSaveGame.XP = AuraAttributes->GetXP();
			PlayerSaveGame.PlayerSaveGame.Strength = AuraAttributes->GetStrength();
			PlayerSaveGame.PlayerSaveGame.Agility = AuraAttributes->GetAgility();
			PlayerSaveGame.PlayerSaveGame.Intelligence = AuraAttributes->GetIntelligence();
			for (const auto& temp : GetActivatableAbilities())
			{
				if (temp.Ability->GetAssetTags().First().MatchesTag(Aura::Abilities::Attack::Attack))
				{
					FAbilitiesSaveGame AbilitiesSaveGame;
					AbilitiesSaveGame.AbilityTag = temp.Ability->GetAssetTags().First();
					if (AbilityInputBindings.Contains(temp.Ability->GetAssetTags().First()))
					{
						AbilitiesSaveGame.InputTag = *AbilityInputBindings.Find(temp.Ability->GetAssetTags().First());
					}
					AbilitiesSaveGame.AbilityLevel = temp.Level;
					PlayerSaveGame.PlayerSaveGame.AbilitiesSaveGame.Add(AbilitiesSaveGame);
				}
			}
			SaveGameArray.Add(PlayerSaveGame);
		});
}

void UAuraASC::PlayerLoadGame()
{
	if (GetNetMode() == ENetMode::NM_Standalone && Cast<APlayerState>(GetOwnerActor()) && UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGame)
	{
		TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
		GetAllAbilities(OutAbilityHandles);
		for (auto& SpecHandle : OutAbilityHandles)
			if (FindAbilitySpecFromHandle(SpecHandle)->Ability->GetAssetTags().HasTag(Aura::Abilities::Attack::Attack))
			{
				ClearAbility(SpecHandle);
				AbilityInputBindings.Empty();
			}
		auto SaveGame = UAuraSubSystem::GetAuraSubSystem(this)->AuraSaveGame;
		for (const auto& temp : SaveGame->ObjectData)
			if (temp.ID == CombatCharacter->GetCharacterID())
			{
				for (const auto& temp1 : temp.PlayerSaveGame.AbilitiesSaveGame)
				{
					AbilityInputBindings.Remove(temp1.AbilityTag);
					auto temp2 = AbilityInputBindings.FindKey(temp1.InputTag);
					if (temp2) AbilityInputBindings.Remove(*temp2);
					AbilityInputBindings.Add(temp1.AbilityTag, temp1.InputTag);
					auto SpecHandle = GiveAbility(FGameplayAbilitySpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->AbilitiesClasses[temp1.AbilityTag].AbilityClass));
					FindAbilitySpecFromHandle(SpecHandle)->Level = temp1.AbilityLevel;
					MarkAbilitySpecDirty(*FindAbilitySpecFromHandle(SpecHandle)); // no need for this but *_*
				}
				FGameplayEffectSpecHandle Handle = MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[Aura::Effects::LoadSetByCaller],1,MakeEffectContext());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Handle,Aura::SetByCaller::Health,temp.CharacterSaveGame.Health - AuraAttributes->GetHealth());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Handle,Aura::SetByCaller::Mana,temp.CharacterSaveGame.Mana - AuraAttributes->GetMana());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Handle,Aura::SetByCaller::XP,temp.PlayerSaveGame.XP - AuraAttributes->GetXP());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Handle,Aura::SetByCaller::Strength,temp.PlayerSaveGame.Strength - AuraAttributes->GetStrength());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Handle,Aura::SetByCaller::Agility,temp.PlayerSaveGame.Agility - AuraAttributes->GetAgility());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Handle,Aura::SetByCaller::Intelligence,temp.PlayerSaveGame.Intelligence - AuraAttributes->GetIntelligence());
				ApplyGameplayEffectSpecToSelf(*Handle.Data);
			}
	}
}

void UAuraASC::PlayerUnlockAbility()
{
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
	UAuraSubSystem::GetAuraSubSystem(this)->OnUnlockAbility.AddLambda([this](FGameplayTag AbilityTag)
	{
		Server_PlayerUnlockAbility(AbilityTag);
	});
}
void UAuraASC::Server_PlayerUnlockAbility_Implementation(FGameplayTag AbilityTag)
{
	GiveAbility(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->AbilitiesClasses[AbilityTag].AbilityClass);
	ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[Aura::Effects::CosumeXP],1,MakeEffectContext()).Data.Get());
}
void UAuraASC::PlayerLevelUpAbility()
{
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
		UAuraSubSystem::GetAuraSubSystem(this)->OnNeedLevelUpAbility.AddLambda([this](FGameplayTag AbilityTag)
		{
			Server_AbilityLevelUp(AbilityTag);
		});
}
void UAuraASC::PlayerChangeAbilityInputBinding()
{
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
		UAuraSubSystem::GetAuraSubSystem(this)->OnAssignAbilityToInput.AddLambda([this](FGameplayTagContainer AbilityToInputTags)
		{
			for (const auto& AbilityToInputTag : AbilityToInputTags)
				if (AbilityToInputTag.MatchesTag(Aura::Abilities::Abilities))
				{
					AbilityInputBindings.Remove(AbilityToInputTag);
					for (const auto& temp : AbilityToInputTags)
						if (temp.MatchesTag(Aura::InputActions::InputActions))
						{
							auto temp1 = AbilityInputBindings.FindKey(temp);
							if (temp1)
								AbilityInputBindings.Remove(*temp1);
							AbilityInputBindings.Add(AbilityToInputTag,temp);
						}
					break;
				}
		});
}
void UAuraASC::IsUIReadyForPlayerInitializeStartupAttributes()
{
	if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
		UAuraFunctionLibrary::TickFuncUntil(this,[this]()
		{
			return Cast<IHUDInterface>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->IsUserWidgetValid();
		},[this]()
		{
			Server_PlayerInitializeStartupAttributes();
			PlayerLoadGame();
		});
}
void UAuraASC::IsUIReadyForSSimulatedPlayersToInitializeStartupAttributes() const
{
	if (!Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
		UAuraFunctionLibrary::TickFuncUntil(this,[this]()
		{
			return UAuraAttributes::GetHealthAttribute().GetNumericValue(AuraAttributes.Get()) != 0 && UAuraAttributes::GetManaAttribute().GetNumericValue(AuraAttributes.Get()) != 0;
		},[this]() 
		{
			UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.Broadcast(GetAvatarActor()->GetName(),UAuraAttributes::GetMaxHealthAttribute().GetName(),UAuraAttributes::GetMaxHealthAttribute().GetNumericValue(AuraAttributes.Get()));
			UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.Broadcast(GetAvatarActor()->GetName(),UAuraAttributes::GetMaxManaAttribute().GetName(),UAuraAttributes::GetMaxManaAttribute().GetNumericValue(AuraAttributes.Get()));
			UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.Broadcast(GetAvatarActor()->GetName(),UAuraAttributes::GetHealthAttribute().GetName(),UAuraAttributes::GetHealthAttribute().GetNumericValue(AuraAttributes.Get()));
			UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.Broadcast(GetAvatarActor()->GetName(),UAuraAttributes::GetManaAttribute().GetName(),UAuraAttributes::GetManaAttribute().GetNumericValue(AuraAttributes.Get()));
		});
}
void UAuraASC::IsUIReadyForEnemyInitializeStartupAttributes()
{
	UAuraFunctionLibrary::TickFuncUntil(this,[this](){return CombatCharacter->IsWidgetComponentValid();},[this](){EnemyInitializeStartupAttributes();});
}
void UAuraASC::PlayerBroadcastAttributeChange()
{
		for (const auto& temp : AuraAttributes->FuncPointers)
			GetGameplayAttributeValueChangeDelegate(temp()).AddLambda([this](const FOnAttributeChangeData& Data)
			{
				if (Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
					UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.Broadcast(Data.Attribute.GetName(),Data.Attribute.GetNumericValue(AuraAttributes.Get()));
				if (!Cast<APawn>(GetAvatarActor())->IsLocallyControlled())
					if (AuraAttributes->GetHealthAttribute() == Data.Attribute || AuraAttributes->GetMaxHealthAttribute() == Data.Attribute || AuraAttributes->GetManaAttribute() == Data.Attribute || AuraAttributes->GetMaxManaAttribute() == Data.Attribute)
						UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.Broadcast(GetAvatarActor()->GetName(),Data.Attribute.GetName(),Data.Attribute.GetNumericValue(AuraAttributes.Get()));
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
	{
		ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[Aura::Effects::CosumeXP],1,MakeEffectContext()).Data.Get());
		ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[InputTag],1,MakeEffectContext()).Data.Get());
	}
}
void UAuraASC::PlayerInitializeStartupAttributes()
{
	if (Cast<APawn>(GetAvatarActor())->HasAuthority())
		for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartupAttributes)
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[temp],1,MakeEffectContext()).Data.Get());
}
void UAuraASC::BroadcastAttributeChangeForWidgetComp()
{
	for (const auto& temp : AuraAttributes->FuncPointers)
		GetGameplayAttributeValueChangeDelegate(temp()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			if (AuraAttributes->GetHealthAttribute() == Data.Attribute || AuraAttributes->GetMaxHealthAttribute() == Data.Attribute || AuraAttributes->GetManaAttribute() == Data.Attribute || AuraAttributes->GetMaxManaAttribute() == Data.Attribute)
				UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.Broadcast(GetAvatarActor()->GetName(),Data.Attribute.GetName(),Data.Attribute.GetNumericValue(AuraAttributes.Get()));
		});
}
void UAuraASC::EnemyInitializeStartupAttributes()
{
	if (Cast<APawn>(GetOwner())->HasAuthority())
		for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartupAttributes)
			ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[temp],1,MakeEffectContext()).Data.Get());
}
void UAuraASC::Server_AbilityLevelUp_Implementation(const FGameplayTag& AbilityTag)
{
	auto temp = Cast<IAttributeInterface>(GetAvatarActor())->GetAuraAttributes();
	if (temp->GetXP() >= temp->GetMaxXP())
	{
		TArray<FGameplayAbilitySpec*> MatchingGameplayAbilities;
		GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTag.GetSingleTagContainer(),MatchingGameplayAbilities);
		MatchingGameplayAbilities[0]->Level++;
		MarkAbilitySpecDirty(*MatchingGameplayAbilities[0]);
		ApplyGameplayEffectSpecToSelf(*MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[Aura::Effects::CosumeXP],1,MakeEffectContext()).Data.Get());
	}
}
void UAuraASC::Server_PlayerInitializeStartupAttributes_Implementation()
{
	PlayerInitializeStartupAttributes();
	InitializeAbilities(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartUpAbilities);
}
void UAuraASC::InitializeAbilities(TArray<FGameplayTag> AbilitiesTags)
{
	if (Cast<APawn>(GetAvatarActor())->HasAuthority())
		for (const auto& temp : AbilitiesTags)
			GiveAbility(FGameplayAbilitySpec(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->AbilitiesClasses[temp].AbilityClass));
}
void UAuraASC::OnDeath() const
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
		if (AbilityInputBindings.FindKey(Key))
			TryActivateAbilitiesByTag(AbilityInputBindings.FindKey(Key)->GetSingleTagContainer());
	});
	UAuraSubSystem::GetAuraSubSystem(this)->OnInputReleased.AddLambda([this](FGameplayTag Key)
	{
		TArray<FGameplayAbilitySpec*> MatchingGameplayAbilities;
		if (AbilityInputBindings.FindKey(Key))
			GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityInputBindings.FindKey(Key)->GetSingleTagContainer(),MatchingGameplayAbilities);
		if (MatchingGameplayAbilities.Num() == 0) 
			return;
		FGameplayTagContainer ReleaseInputsAbilities;
		ReleaseInputsAbilities.AddTag(Aura::Abilities::Attack::Arcane);
		ReleaseInputsAbilities.AddTag(Aura::Abilities::Attack::Electrocute);
		if (MatchingGameplayAbilities[0]->Ability.Get()->GetAssetTags().HasAnyExact(ReleaseInputsAbilities))
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,MatchingGameplayAbilities[0]->Handle,
				MatchingGameplayAbilities[0]->GetPrimaryInstance()->GetCurrentActivationInfo().GetActivationPredictionKey());
	});
}
