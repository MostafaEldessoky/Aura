// Mostafa Eldesouky


#include "AbilitySystem/Cues/DeathBehavior.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Data/AuraData.h"
#include "Interfaces/Combat.h"
#include "Statics/AuraSubSystem.h"

bool UDeathBehavior::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	 Cast<ICombat>(MyTarget)->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	 Cast<ICombat>(MyTarget)->GetCapsule()->SetCollisionResponseToChannel(
		UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.MouseTraceChannel, 
		ECR_Ignore);
	 Cast<ICombat>(MyTarget)->GetModelMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	 Cast<ICombat>(MyTarget)->GetModelMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	 Cast<ICombat>(MyTarget)->GetModelMesh()->SetSimulatePhysics(true);
	 Cast<ICombat>(MyTarget)->GetModelMesh()->SetEnableGravity(true);
	 Cast<ICombat>(MyTarget)->GetModelMesh()->GetAnimInstance()->StopAllMontages(0.1);
	 Cast<ICombat>(MyTarget)->GetWeaponMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	 Cast<ICombat>(MyTarget)->GetWeaponMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	 Cast<ICombat>(MyTarget)->GetWeaponMesh()->SetSimulatePhysics(true);
	 Cast<ICombat>(MyTarget)->GetWeaponMesh()->SetEnableGravity(true);
	 Cast<ICombat>(MyTarget)->GetWeaponMesh()->DetachFromParent();
	
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}
