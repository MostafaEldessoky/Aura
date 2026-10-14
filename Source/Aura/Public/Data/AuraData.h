// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "ScalableFloat.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "AuraData.generated.h"

class UBehaviorTree;
class AAuraEnemyBase;
class UNiagaraSystem;
class AProjectile;
class UGameplayAbility;
class UGameplayEffect;
class UInputAction;
class UInputMappingContext;
class UAttributeSet;

UENUM() enum class EDamageType : uint8
{
	None,
	Physical,
	Magical
};
USTRUCT(Blueprintable) struct FCharacterData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> StartupAttributes;
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> StartUpAbilities;
	UPROPERTY(EditDefaultsOnly)
	FName WeaponMeshSocketName;
	UPROPERTY(EditDefaultsOnly)
	FName WeaponMechanicSocketName;
	UPROPERTY(EditDefaultsOnly)
	FName MotionWarpingTargetName;
	UPROPERTY(EditDefaultsOnly)
	int32 HighlightValueColor;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> CharacterClass;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,UAnimMontage*> Montages;
};
USTRUCT(Blueprintable) struct FCollisionsData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> MouseTraceChannel;
	UPROPERTY(EditDefaultsOnly)
	FName CapsuleCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	FName MeshCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	FName WeaponCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	FName ItemCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	FName ProjectileProfileName;
};
USTRUCT(Blueprintable) struct FItemsData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ItemEffect;
	UPROPERTY(EditDefaultsOnly)
	float ItemLevel;
};
USTRUCT(Blueprintable) struct FInputsData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,UInputMappingContext*> InputMappingContext;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,UInputAction*> InputActionsStarted;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,UInputAction*> InputActionsCompleted;
};
USTRUCT(Blueprintable) struct FUIData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag MassageTag;
	UPROPERTY(EditDefaultsOnly)
	FText MassageText;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* MassageImage;
};
USTRUCT(BlueprintType) struct FBuffData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute EffectedAttribute;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GrantedTag;
	UPROPERTY(EditDefaultsOnly)
	float Chance;
	UPROPERTY(EditDefaultsOnly)
	float Damage;
	UPROPERTY(EditDefaultsOnly)
	float Duration;
	UPROPERTY(EditDefaultsOnly)
	float Period;
	UPROPERTY(EditDefaultsOnly)
	FGameplayEffectCue GameplayCues;
};
USTRUCT(BlueprintType) struct FAbilitiesData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;
	UPROPERTY(EditDefaultsOnly)
	EDamageType DamageType;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat Damage;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat Cost;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat Cooldown;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer PassiveTags;
	UPROPERTY(EditDefaultsOnly)
	TArray<FBuffData> BuffsToApply;
};
UCLASS(Blueprintable)
class AURA_API UAuraData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FCollisionsData CollisionsData;
	UPROPERTY(EditDefaultsOnly)
	FInputsData InputData;
	UPROPERTY(EditDefaultsOnly)
	TArray<FItemsData> ItemsData;
	UPROPERTY(EditDefaultsOnly)
	TArray<FUIData> UIData;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,FCharacterData> DataPerCharacter;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,FAbilitiesData> AbilitiesClasses;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,TSubclassOf<UGameplayEffect>> EffectsClasses;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,TSubclassOf<AProjectile>> ProjectilesClasses;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,int32> OnApplyEffectsToTargetOrder;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,int32> OnApplyEffectsToSelfOrder;
};
