// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraASC.generated.h"


class UAuraAttributes;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UAuraASC();
	virtual void BeginPlay() override;
private:
	UFUNCTION(Client, Reliable)
	void Client_BroadCastPickUpItem(const FGameplayEffectSpec& SpecApplied);
	UFUNCTION(Server, Reliable)
	void Server_ApplyLevelUpEffect(const FString& AttributeName);
	TWeakObjectPtr<UAuraAttributes> AuraAttributes;
	FTimerHandle InitializeStartupAttributesTimerHandle;
	void PlayerBroadcastAttributeChange();
    void PlayerLevelUp();
    void PlayerInitializeStartupAttributes();
    void EnemyBroadcastAttributeChange();
    void EnemyInitializeStartupAttributes();
	void InitializePlayerAbilities();
	void InitializeEnemyAbilities();
	void PlayerListenToInputEvents();
};
