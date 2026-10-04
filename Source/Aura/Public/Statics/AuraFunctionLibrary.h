// Mostafa Eldesouky

#pragma once

#include <Functional>
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraFunctionLibrary.generated.h"


class AProjectile;
struct FGameplayEventData;
class UGameplayAbility;
/**
 * 
 */
UCLASS()
class AURA_API UAuraFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void TickFuncUntil(const UObject* WorldContextObject,std::function<bool()> FuncToCheck, std::function<void()> FuncToCall);
	static FGameplayTag MakeAttributeTagFromName(const FString& AttributeName);
	static TArray<FOverlapResult> DoOverlapMultiByChannel(AActor* Instigator,const TArray<AActor*>& IgnoredActors,const FVector& OriginPoint,
		const float RadiusOfEffect);
	static void ApplyEffectToTarget(AActor* Instigator,AActor* Target,const FVector& ImpactPoint,const FGameplayTag& DamageEffectTag,const float AbilityLevel);
	static void ApplyEffectToTargetWithCue_NonReplicated(AActor* Instigator,AActor* Target,const FVector& ImpactPoint,
		const FGameplayTag& CueTag,const FGameplayTag& DamageEffectTag,const float AbilityLevel);
	static void ApplyRadialDamageEffect(AActor* Instigator,const TArray<AActor*>& IgnoredActors,const FVector& OriginPoint,
		const float RadiusOfEffect,const FGameplayTag& DamageEffectTag,const float AbilityLevel);
	static void ApplyRadialDamageEffectWithFallOff(AActor* Instigator,const TArray<AActor*>& IgnoredActors,const FVector& OriginPoint,const float InnerRadiusOfEffect,
	const float OuterRadiusOfEffect,const FGameplayTag& DamageEffectTag,const float InnerAbilityLevel,const float OuterAbilityLevel);
	static AActor* GetNearestLineOfSightActorWithInRadius(AActor* Target,TArray<AActor*> Root,const float SearchRadius);
	static TArray<FVector> GetBoundedVectors(const FVector& StartVector,const FVector& EndVector,const FVector& OriginPoint,const int32& NumOfVectors);
	static void CallFuncOnPointsCollectedOnTheGround(const UObject* WorldContextObject,const bool& IsForAI,FVector StartPoint,const float& RadiusOfActivation, std::function<void(TArray<FVector>&)> FuncToCall);
	static AActor* SpawnProjectile(AActor* Instigator,AActor* Target,FVector TargetLocation,FGameplayTag ProjectileID,float LifeTime,bool bLunchImpulse,const float AbilityLevel);
	static void PlayMontageAndWaitNotify(UGameplayAbility* OwnedAbility,AActor* Instigator,FVector TargetLocation,FGameplayTag PlayedMontageTag, FGameplayTag AnimNotifyTag,FName FuncToCall);
};
