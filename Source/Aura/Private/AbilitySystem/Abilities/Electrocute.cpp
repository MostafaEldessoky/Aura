// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Electrocute.h"

#include "AbilitySystemComponent.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "AbilitySystem/Tasks/AbilityTask_CanAttack.h"
#include "AbilitySystem/Tasks/AbilityTask_TargetDataUnderMouse.h"
#include "Interfaces/Combat.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Statics/AuraFunctionLibrary.h"

void UElectrocute::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto temp = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	temp->OnRelease.AddDynamic(this,&UElectrocute::OnInputReleased);
	temp->ReadyForActivation();
	auto TargetDataTask = UAbilityTask_TargetDataUnderMouse::GetTargetDataUnderMouse(this);
	TargetDataTask->OnTargetDataUnderMouse.AddLambda([this](FHitResult HitResult)
	{
		Target = HitResult;
		if (!HitResult.GetActor()->Implements<UCombat>())
		{
			EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
			return;
		}
		auto CanAttack = UAbilityTask_CanAttack::GetCanAttack(this,HitResult);
		CanAttack->OnCanAttack.AddLambda([this,HitResult]()
		{
			if (GetCurrentActorInfo()->IsLocallyControlled())
				GetCurrentActorInfo()->PlayerController->bShowMouseCursor = false;
			UAuraFunctionLibrary::PlayMontageAndWaitNotify(this,GetAvatarActorFromActorInfo(),HitResult.GetActor()->GetActorLocation(),
				PlayedMontageTag,AnimNotifyTag,STATIC_FUNCTION_FNAME(TEXT("UElectrocute::OnGameplayEventReceivedFromAnimNotify")));
		});
		CanAttack->ReadyForActivation();
	});
	TargetDataTask->ReadyForActivation();
}
void UElectrocute::OnInputReleased(float TimeHeld)
{
	bInputReleased = true;
}
void UElectrocute::OnGameplayEventReceivedFromAnimNotify(FGameplayEventData Payload)
{
	OnApplyingElectrocute();
}
void UElectrocute::OnApplyingElectrocute()
{
	TArray<TWeakObjectPtr<AActor>> TargetActor;
	TargetActor.Init(nullptr,NumberOfTargets);
	FHitResult OutHitResult;
	UKismetSystemLibrary::SphereTraceSingle(
		this,
		GetAvatarActorFromActorInfo()->GetActorLocation(),
		Target.GetActor()->GetActorLocation(),
		50.f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		TArray{GetAvatarActorFromActorInfo()},
		EDrawDebugTrace::None,
		OutHitResult,
		true);
	if (OutHitResult.GetActor() && OutHitResult.GetActor()->Implements<UCombat>())
	{
		TargetActor[0] = OutHitResult.GetActor();
		UAuraFunctionLibrary::ApplyEffectToTarget(GetAvatarActorFromActorInfo(),TargetActor[0].Get(),OutHitResult.ImpactPoint,DamageEffectTag,GetAbilityLevel());
		TArray<AActor*> Roots;
		Roots.Add(GetAvatarActorFromActorInfo());
		for (int32 i = 0; i < NumberOfTargets - 1; i++)
		{
			Roots.Add(TargetActor[i].Get());
			TargetActor[i+1] = UAuraFunctionLibrary::GetNearestLineOfSightActorWithInRadius(
			TargetActor[i].Get(),
			Roots,
			ElectrocuteSearchRadius);
			if (TargetActor[i+1].IsValid())
				UAuraFunctionLibrary::ApplyEffectToTarget(GetAvatarActorFromActorInfo(),TargetActor[i+1].Get(),OutHitResult.ImpactPoint,DamageEffectTag,GetAbilityLevel());
			else
				break;
		}
		if (!bCueActivated)
		{
			bCueActivated = true;
			FGameplayCueParameters CueParams;
			CueParams.EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
			CueParams.EffectContext.AddOrigin(Cast<ICombat>(GetAvatarActorFromActorInfo())->GetWeaponMechanicSocketTransform().GetLocation());
			CueParams.EffectContext.Get()->AddActors(TargetActor);
			if (GetCurrentActorInfo()->IsNetAuthority())
				UGameplayCueFunctionLibrary::AddGameplayCueOnActor(GetAvatarActorFromActorInfo(),CueTag,CueParams);
			else
				UGameplayCueManager::AddGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),CueTag,CueParams);
		}
	}
	else
	{
		if (GetCurrentActorInfo()->IsLocallyControlled())
			GetCurrentActorInfo()->PlayerController->bShowMouseCursor = true;
		bCueActivated = false;
		if (GetCurrentActorInfo()->IsNetAuthority())
			UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(GetAvatarActorFromActorInfo(),CueTag,FGameplayCueParameters());
		else
			UGameplayCueManager::RemoveGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),CueTag,FGameplayCueParameters());
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
		return;
	}
	if (bInputReleased || !CommitAbilityCost(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo))
	{	
		bInputReleased = false;
		bCueActivated = false;
		if (GetCurrentActorInfo()->IsLocallyControlled())
			GetCurrentActorInfo()->PlayerController->bShowMouseCursor = true;
		if (GetCurrentActorInfo()->IsNetAuthority())
			UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(GetAvatarActorFromActorInfo(),CueTag,FGameplayCueParameters());
		else
			UGameplayCueManager::RemoveGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),CueTag,FGameplayCueParameters());
		CommitAbilityCooldown(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true);
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,false,false);
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(ElectrocuteTimerHandle,this, &UElectrocute::OnApplyingElectrocute, 0.2f);
}
