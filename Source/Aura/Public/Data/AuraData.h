// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "AuraData.generated.h"

class UBehaviorTree;
class AAuraEnemyBase;
class UNiagaraSystem;
class AProjectile;
class UGameplayAbility;
class UGameplayEffect;
class UInputAction;
class UInputMappingContext;

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
	TMap<FGameplayTag,TSubclassOf<UGameplayAbility>> AbilitiesClasses;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,TSubclassOf<UGameplayEffect>> EffectsClasses;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,TSubclassOf<AProjectile>> ProjectilesClasses;
};
