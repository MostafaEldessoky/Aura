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
			InitializeAbilities(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].StartUpAbilities);
			PlayerBroadcastAttributeChange();
			PlayerLevelUp();
			PlayerInputs();
			OnDeath();
			GetWorld()->GetTimerManager().SetTimer(InitializeStartupAttributesTimerHandle,this,&UAuraASC::PlayerInitializeStartupAttributes,0.5f,false);
			UAuraSubSystem::GetAuraSubSystem(this)->OnUnlockAbility.AddLambda([this](FGameplayTag AbilityTag)
			{
				GiveAbility(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->AbilitiesClasses[AbilityTag].AbilityClass);
			});
			UAuraSubSystem::GetAuraSubSystem(this)->OnAssignAbilityToInput.AddLambda([this](FGameplayTagContainer AbilityToInputTags)
			{
				for (const auto& AbilityToInputTag : AbilityToInputTags)
					if (AbilityToInputTag.MatchesTag(Aura::Abilities::Abilities))
					{
						TArray<FGameplayAbilitySpec*> OutAbilitySpecs;
						GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityToInputTag.GetSingleTagContainer(),OutAbilitySpecs);
						const_cast<FGameplayTagContainer&>(OutAbilitySpecs[0]->Ability.Get()->GetAssetTags()).Reset();
						for (const auto& temp : AbilityToInputTags)
							const_cast<FGameplayTagContainer&>(OutAbilitySpecs[0]->Ability.Get()->GetAssetTags()).AddTag(temp);
						MarkAbilitySpecDirty(*OutAbilitySpecs[0]);
						break;
					}
			});
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

void UAuraASC::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	if (!Cast<APlayerState>(GetOwner())) 
		return;
	for (const auto& temp : AbilitySpec.Ability.Get()->GetAssetTags())
		if (temp.MatchesTag(Aura::Abilities::Abilities))
			UAuraSubSystem::GetAuraSubSystem(this)->OnGiveAbility.Broadcast(temp);
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
		TryActivateAbilitiesByTag(Key.GetSingleTagContainer());
	});
	UAuraSubSystem::GetAuraSubSystem(this)->OnInputReleased.AddLambda([this](FGameplayTag Key)
	{
		TArray<FGameplayAbilitySpec*> MatchingGameplayAbilities;
		GetActivatableGameplayAbilitySpecsByAllMatchingTags(Key.GetSingleTagContainer(),MatchingGameplayAbilities);
		if (MatchingGameplayAbilities.Num() == 0) 
			return;
		FGameplayTagContainer ReleaseInputsAbilities;
		ReleaseInputsAbilities.AddTag(Aura::Abilities::Arcane);
		ReleaseInputsAbilities.AddTag(Aura::Abilities::Electrocute);
		if (MatchingGameplayAbilities[0]->Ability.Get()->GetAssetTags().HasAnyExact(ReleaseInputsAbilities))
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,MatchingGameplayAbilities[0]->Handle,
				MatchingGameplayAbilities[0]->GetPrimaryInstance()->GetCurrentActivationInfo().GetActivationPredictionKey());
	});
}
