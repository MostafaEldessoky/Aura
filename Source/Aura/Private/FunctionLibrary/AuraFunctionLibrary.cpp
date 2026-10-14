// Mostafa Eldesouky


#include "Statics/AuraFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "GameplayEffectTypes.h"
#include "NavigationSystem.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/SphereComponent.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Interfaces/Combat.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Projectiles/Projectile.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"
#include "Statics/AuraSubSystem.h"


void UAuraFunctionLibrary::TickFuncUntil(const UObject* WorldContextObject,std::function<bool()> FuncToCheck, std::function<void()> FuncToCall)
{
	if (!FuncToCheck())
	{
		WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick([WorldContextObject,FuncToCheck,FuncToCall]()
		{
			TickFuncUntil(WorldContextObject,FuncToCheck,FuncToCall);
		});
		return;
	}
	FuncToCall();
}
FGameplayTag UAuraFunctionLibrary::MakeAttributeTagFromName(const FString& AttributeName)
{
	return FGameplayTag::RequestGameplayTag(FName("Aura.Effects." + AttributeName));
}
TArray<FOverlapResult> UAuraFunctionLibrary::DoOverlapMultiByChannel(AActor* Instigator,
	const TArray<AActor*>& IgnoredActors, const FVector& OriginPoint, const float RadiusOfEffect)
{
	TArray<FOverlapResult> OutOverlaps;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(RadiusOfEffect);
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(IgnoredActors);
	Instigator->GetWorld()->OverlapMultiByChannel(
		OutOverlaps,
		OriginPoint,
		FRotator::ZeroRotator.Quaternion(),
		UAuraSubSystem::GetAuraSubSystem(Instigator)->AuraData->CollisionsData.MouseTraceChannel,
		CollisionShape,
		Params);
	return OutOverlaps;
}
void UAuraFunctionLibrary::ApplyEffectToTarget(AActor* Instigator, AActor* Target,const FVector& ImpactPoint, const FGameplayTag& EffectTag,const FGameplayTag& AbilityTag,
	const float AbilityLevel)
{
	auto temp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Instigator);
	auto temp1 = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!temp || !temp1) return;
	auto EffectContext = temp->MakeEffectContext();
	EffectContext.AddActors(TArray{TWeakObjectPtr(Target)});
	EffectContext.AddOrigin(ImpactPoint);
	
	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	temp->GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTag.GetSingleTagContainer(),AbilitySpecs);
	
	EffectContext.SetAbility(AbilitySpecs[0]->Ability);
	
	auto EffectSpecHandle = temp->MakeOutgoingSpec(UAuraSubSystem::GetAuraSubSystem(Instigator)->AuraData->EffectsClasses[EffectTag],
		AbilityLevel,EffectContext);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle,Aura::SetByCaller::Damage,
		UAuraSubSystem::GetAuraSubSystem(Instigator)->AuraData->AbilitiesClasses[AbilityTag].Damage.GetValueAtLevel(AbilityLevel));
	
	temp->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data,temp1);
}
void UAuraFunctionLibrary::ApplyEffectToTargetWithCue_NonReplicated(AActor* Instigator,AActor* Target,const FVector& ImpactPoint,
                                                      const FGameplayTag& CueTag,const FGameplayTag& DamageEffectTag,const FGameplayTag& AbilityTag,const float AbilityLevel)
{
	FGameplayCueParameters CueParams;
	CueParams.Location = ImpactPoint;
	UGameplayCueManager::ExecuteGameplayCue_NonReplicated(Target,CueTag, CueParams);
	ApplyEffectToTarget(Instigator,Target,ImpactPoint,DamageEffectTag,AbilityTag,AbilityLevel);
}
void UAuraFunctionLibrary::ApplyRadialDamageEffect(AActor* Instigator,const TArray<AActor*>& IgnoredActors,const FVector& OriginPoint,
	const float RadiusOfEffect,const FGameplayTag& DamageEffectTag,const FGameplayTag& AbilityTag,const float AbilityLevel)
{
	for (const auto& OutOverlap : DoOverlapMultiByChannel(Instigator,IgnoredActors,OriginPoint,RadiusOfEffect))
		ApplyEffectToTarget(Instigator,OutOverlap.GetActor(),OutOverlap.GetActor()->GetActorLocation(),DamageEffectTag,AbilityTag,AbilityLevel);
}
void UAuraFunctionLibrary::ApplyRadialDamageEffectWithFallOff(AActor* Instigator,const TArray<AActor*>& IgnoredActors,const FVector& OriginPoint,const float InnerRadiusOfEffect,
	const float OuterRadiusOfEffect,const FGameplayTag& DamageEffectTag,const FGameplayTag& AbilityTag,const float InnerAbilityLevel,const float OuterAbilityLevel)
{
	for (const auto& OutOverlap : DoOverlapMultiByChannel(Instigator,IgnoredActors,OriginPoint,OuterRadiusOfEffect))
		if ((OriginPoint - OutOverlap.GetActor()->GetActorLocation()).Size() <= InnerRadiusOfEffect)
			ApplyEffectToTarget(Instigator,OutOverlap.GetActor(),OutOverlap.GetActor()->GetActorLocation(),AbilityTag,DamageEffectTag,InnerAbilityLevel);
		else 
			ApplyEffectToTarget(Instigator,OutOverlap.GetActor(),OutOverlap.GetActor()->GetActorLocation(),DamageEffectTag,AbilityTag,
				InnerAbilityLevel - ((OriginPoint - OutOverlap.GetActor()->GetActorLocation()).Size() - InnerRadiusOfEffect) / (OuterRadiusOfEffect - InnerRadiusOfEffect) * (InnerAbilityLevel - OuterAbilityLevel));
}
AActor* UAuraFunctionLibrary::GetNearestLineOfSightActorWithInRadius(AActor* Target,TArray<AActor*> Root,const float SearchRadius)
{
	Root.Add(Target);
	FHitResult OutHitResult;
	TMap<AActor*,float> ActorsAndDistances;
	float NearestActorDistance = 0.f;
	AActor* NearestActor = nullptr;
	FVector NearestActorLocation = Target->GetActorForwardVector() * SearchRadius ;
	for (const auto& temp : DoOverlapMultiByChannel(Target,Root, Target->GetActorLocation(), SearchRadius))
		if ((Target->GetActorLocation() - temp.GetActor()->GetActorLocation()).Size2D() <= (Target->GetActorLocation() - NearestActorLocation).Size2D())
		{
			NearestActor = temp.GetActor();
			NearestActorLocation = temp.GetActor()->GetActorLocation();
			NearestActorDistance = (Target->GetActorLocation() - temp.GetActor()->GetActorLocation()).Size2D();
			ActorsAndDistances.Add(NearestActor,NearestActorDistance);
		}
	if (!NearestActor) 
		return nullptr;
	UKismetSystemLibrary::SphereTraceSingle(
		Target,
		Target->GetActorLocation(),
		NearestActor->GetActorLocation(),
		50.f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		Root,
		EDrawDebugTrace::None,
		OutHitResult,
		true);
	if (OutHitResult.GetActor() == NearestActor)
		return NearestActor;

	ActorsAndDistances.FindAndRemoveChecked(NearestActor);
	ActorsAndDistances.ValueSort([](int32 A, int32 B){return A < B; });
	for (const auto& temp : ActorsAndDistances)
	{
		UKismetSystemLibrary::SphereTraceSingle(
			Target,
			Target->GetActorLocation(),
			temp.Key->GetActorLocation(),
			50.f,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			Root,
			EDrawDebugTrace::None,
			OutHitResult,
			true);
		if (OutHitResult.GetActor() == temp.Key)
			return temp.Key;
	}
	return nullptr;
}
TArray<FVector> UAuraFunctionLibrary::GetBoundedVectors(const FVector& StartVector,const FVector& EndVector,const FVector& OriginPoint,const int32& NumOfVectors)
{
	float Angle;
		
	if (StartVector == EndVector)
		Angle = 360;
	else
		Angle = UKismetMathLibrary::DegAcos(UKismetMathLibrary::Vector_CosineAngle2D(StartVector,EndVector));
	
	Angle /= NumOfVectors;
	TArray<FVector> RotatedVectors;
	for (int32 i = 0; i < NumOfVectors; i++)
	{
		RotatedVectors.Add(OriginPoint + UKismetMathLibrary::RotateAngleAxis(StartVector,Angle*i,FVector(0,0,1)));
	}
	return RotatedVectors;
}
void UAuraFunctionLibrary::CallFuncOnPointsCollectedOnTheGround(const UObject* WorldContextObject,const bool& IsForAI,FVector StartPoint,const float& RadiusOfActivation, std::function<void(TArray<FVector>&)> FuncToCall)
{
	StartPoint.Z = 1000.f;
	FVector StartVector =  FVector( RadiusOfActivation,0,0);
	TArray<FVector> PointsOnAir = GetBoundedVectors(StartVector,StartVector,StartPoint,6);
	PointsOnAir.Add(StartPoint);
	TArray<FVector> PointsOnTheGround;
	for (const auto& temp :  PointsOnAir)
	{
		FHitResult HitResult;
		WorldContextObject->GetWorld()->LineTraceSingleByChannel(HitResult,temp,FVector(temp.X,temp.Y,-1000.f),
			UAuraSubSystem::GetAuraSubSystem(WorldContextObject)->AuraData->CollisionsData.MouseTraceChannel);
		if (!Cast<ICombat>(HitResult.GetActor()))
		{
			auto NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(WorldContextObject->GetWorld());
			if (IsForAI && NavSys)
			{
				FNavLocation ProjectedLocation;
				if (NavSys->ProjectPointToNavigation(HitResult.ImpactPoint, ProjectedLocation))
					PointsOnTheGround.Add(ProjectedLocation.Location);
			}
			else
				PointsOnTheGround.Add(HitResult.ImpactPoint);
		}
	}
	Test::Shuffle(PointsOnTheGround);
	FuncToCall(PointsOnTheGround);
}
AActor* UAuraFunctionLibrary::SpawnProjectile(AActor* Instigator,AActor* Target,FVector TargetLocation,FGameplayTag ProjectileID,float LifeTime,bool bLunchImpulse,bool bRotate,const FGameplayTag& AbilityTag,const float AbilityLevel)
{
	if (!Instigator->HasAuthority()) return nullptr;
	TScriptInterface<ICombat> CombatCharacter = Instigator;
	if (!CombatCharacter) return nullptr;
	auto SpawnedActor = Instigator->GetWorld()->SpawnActorDeferred<AProjectile>(
		UAuraSubSystem::GetAuraSubSystem(Instigator)->AuraData->ProjectilesClasses[ProjectileID],
		CombatCharacter->GetWeaponMechanicSocketTransform(),
		Instigator
	);
	SpawnedActor->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(CombatCharacter->GetWeaponMechanicSocketTransform().GetLocation(),TargetLocation));
	SpawnedActor->AbilityLevel = AbilityLevel;
	SpawnedActor->LifeTime = LifeTime;
	SpawnedActor->AssetTag = AbilityTag;
	if (bRotate)
	{
		SpawnedActor->ProjectileMovementComponent->Deactivate();
		SpawnedActor->AttachToActor(Instigator,FAttachmentTransformRules::KeepWorldTransform);
		SpawnedActor->SetActorLocation(Instigator->GetActorLocation());
		SpawnedActor->RotatingMovementComponent->RotationRate = FRotator(0.f,200.f,0.f);
		SpawnedActor->RotatingMovementComponent->PivotTranslation = FVector(200,0,0);
	}
	if (bLunchImpulse)
	{
		SpawnedActor->ProjectileMovementComponent->AddForce(FVector(0,0,100));
		SpawnedActor->ProjectileMovementComponent->ProjectileGravityScale = 1.f;
	}
	if (Target)
	{
		SpawnedActor->ProjectileMovementComponent->bIsHomingProjectile = true;
		SpawnedActor->ProjectileMovementComponent->bRotationFollowsVelocity = true;
		SpawnedActor->ProjectileMovementComponent->HomingAccelerationMagnitude = 2000.f;
		SpawnedActor->ProjectileMovementComponent->HomingTargetComponent = Target->GetRootComponent();
		Cast<ICombat>(Target)->GetOnDeathDelegate().AddLambda([SpawnedActor](AActor*)
		{
			SpawnedActor->ProjectileMovementComponent->HomingTargetComponent = nullptr;
		});
	}
	SpawnedActor->FinishSpawning(CombatCharacter->GetWeaponMechanicSocketTransform());
	return SpawnedActor;
}

void UAuraFunctionLibrary::PlayMontageAndWaitNotify(UGameplayAbility* OwnedAbility,AActor* Instigator,FVector TargetLocation,
	FGameplayTag PlayedMontageTag, FGameplayTag AnimNotifyTag,FName FuncToCall)
{
	TScriptInterface<ICombat> CombatCharacter = OwnedAbility->GetAvatarActorFromActorInfo();
	CombatCharacter->TargetMotionWarping(TargetLocation);
	auto PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(OwnedAbility,FName(),
		UAuraSubSystem::GetAuraSubSystem(Instigator)->AuraData->DataPerCharacter[CombatCharacter->GetCharacterID()].Montages[PlayedMontageTag]);
	PlayMontageAndWait->ReadyForActivation();
	auto WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(OwnedAbility,AnimNotifyTag);
	FScriptDelegate DynamicDelegate;
	DynamicDelegate.BindUFunction(OwnedAbility, FuncToCall);
	WaitGameplayEvent->EventReceived.Add(DynamicDelegate);
	WaitGameplayEvent->ReadyForActivation();
}

