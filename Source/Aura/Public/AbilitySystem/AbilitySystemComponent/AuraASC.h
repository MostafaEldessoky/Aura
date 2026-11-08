// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraASC.generated.h"


class ICombat;
class UAuraAttributes;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UAuraASC();
	virtual void BeginPlay() override;
protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
private:
	UFUNCTION(Client, Reliable)
	void Client_BroadCastPickUpItem(const FGameplayTagContainer& SpecApplied);
	UFUNCTION(Server, Reliable)
	void Server_ApplyLevelUpEffect(const FString& AttributeName);
	UFUNCTION(Server, Reliable)
	void Server_AbilityLevelUp(const FGameplayTag& AbilityTag);
	UFUNCTION(Server, Reliable)
	void Server_PlayerInitializeStartupAttributes();
	UFUNCTION(Server, Reliable)
	void Server_PlayerUnlockAbility(FGameplayTag AbilityTag);
	void PlayerSaveGame();
	void PlayerLoadGame();
	void PlayerUnlockAbility();
	void PlayerLevelUpAbility();
	void PlayerChangeAbilityInputBinding();
	void IsUIReadyForPlayerInitializeStartupAttributes();
	void IsUIReadyForSSimulatedPlayersToInitializeStartupAttributes() const;
	void IsUIReadyForEnemyInitializeStartupAttributes();
	void InitializeAbilities(TArray<FGameplayTag> AbilitiesTags);
	void PlayerBroadcastAttributeChange();
	void PlayerLevelUp();
	void PlayerInitializeStartupAttributes();
	void BroadcastAttributeChangeForWidgetComp();
	void EnemyInitializeStartupAttributes();
	void OnDeath() const;
	void PlayerInputs();
	TWeakObjectPtr<UAuraAttributes> AuraAttributes;
	TScriptInterface<ICombat> CombatCharacter;
	TMap<FGameplayTag, FGameplayTag> AbilityInputBindings;
};
