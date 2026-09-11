// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "AuraData.generated.h"

class UGameplayAbility;
class UGameplayEffect;
struct FGameplayTag;
class UInputAction;
class UInputMappingContext;

USTRUCT(Blueprintable) struct FCharacterBaseData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FName WeaponMeshSocketName;
	UPROPERTY(EditDefaultsOnly)
	FName CapsuleCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	FName MeshCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	FName WeaponCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> StartupAttributes;
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel;
};
USTRUCT(Blueprintable) struct FAuraPlayerData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> TraceChannel;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};
USTRUCT(Blueprintable) struct FAuraEnemyData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	int32 HighlightValueColor;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};
USTRUCT(Blueprintable) struct FItemEffectData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GamePlayEffectClass;
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ItemTag;
};
USTRUCT(Blueprintable) struct FItemData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FName BoxCollisionProfileName;
	UPROPERTY(EditDefaultsOnly)
	TArray<FItemEffectData> ItemsEffect;
};
USTRUCT(Blueprintable) struct FInputData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,UInputMappingContext*> InputMappingContext;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,UInputAction*> InputActions;
};
USTRUCT(Blueprintable) struct FLevelUpData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> EffectClass;
	UPROPERTY(EditDefaultsOnly)
	int8 EffectLevel;
};
USTRUCT(Blueprintable) struct FUIMassageData
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
	FCharacterBaseData CharacterBaseData;
	UPROPERTY(EditDefaultsOnly)
	FAuraPlayerData PlayerData;
	UPROPERTY(EditDefaultsOnly)
	FAuraEnemyData EnemyData;
	UPROPERTY(EditDefaultsOnly)
	FItemData ItemData;
	UPROPERTY(EditDefaultsOnly)
	FInputData InputData;
	UPROPERTY(EditDefaultsOnly)
	TMap<FString,FLevelUpData> LevelUpData;
	UPROPERTY(EditDefaultsOnly)
	TArray<FUIMassageData> MassageData;
};
