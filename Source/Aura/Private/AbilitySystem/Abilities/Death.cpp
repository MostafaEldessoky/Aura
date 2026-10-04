// Mostafa Eldesouky


#include "AbilitySystem/Abilities/Death.h"
#include "GameplayCueFunctionLibrary.h"
#include "GameplayCueManager.h"
#include "Components/CapsuleComponent.h"
#include "Data/AuraData.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraSubSystem.h"

void UDeath::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// to be call all of this from cue
	CombatCharacter = GetAvatarActorFromActorInfo();
	CombatCharacter->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCharacter->GetCapsule()->SetCollisionResponseToChannel(
		UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.MouseTraceChannel, 
		ECR_Ignore);
	CombatCharacter->GetModelMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CombatCharacter->GetModelMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	CombatCharacter->GetModelMesh()->SetSimulatePhysics(true);
	CombatCharacter->GetModelMesh()->SetEnableGravity(true);
	CombatCharacter->GetModelMesh()->GetAnimInstance()->StopAllMontages(0.1);
	CombatCharacter->GetWeaponMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	CombatCharacter->GetWeaponMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CombatCharacter->GetWeaponMesh()->SetSimulatePhysics(true);
	CombatCharacter->GetWeaponMesh()->SetEnableGravity(true);
	CombatCharacter->GetWeaponMesh()->DetachFromParent();
	GetAvatarActorFromActorInfo()->SetLifeSpan(5.f);
	//
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(GetAvatarActorFromActorInfo(),DissolveCueTag,FGameplayCueParameters());
	EndAbility(Handle,ActorInfo ,ActivationInfo,false,false);
}
