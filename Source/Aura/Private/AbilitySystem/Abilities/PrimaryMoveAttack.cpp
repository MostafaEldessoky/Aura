// Mostafa Eldesouky


#include "AbilitySystem/Abilities/PrimaryMoveAttack.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Data/Tags.h"

UPrimaryMoveAttack::UPrimaryMoveAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(Tags::Inputs::InputActions::AttackMove);
	SetAssetTags(AssetTags);
}

void UPrimaryMoveAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Warning, TEXT("PrimaryMoveAttack Activated"));
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(ActorInfo->PlayerController.Get(), );
}
