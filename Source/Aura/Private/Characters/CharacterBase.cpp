// Mostafa Eldesouky


#include "Characters/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Data/AuraData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Statics/AuraSubSystem.h"
#include "MotionWarpingComponent.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh());
	bReplicates = true;
	SetReplicatingMovement(true);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
}
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	WeaponMesh->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CharacterTagID].WeaponMeshSocketName);
	WeaponMesh->SetCollisionProfileName(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.WeaponCollisionProfileName);
	GetMesh()->SetCollisionProfileName(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.MeshCollisionProfileName);
	GetCapsuleComponent()->SetCollisionProfileName(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.CapsuleCollisionProfileName);
}
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}
UAuraAttributes* ACharacterBase::GetAuraAttributes() const
{
	return nullptr;
}
void ACharacterBase::Highlight()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMesh->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CharacterTagID].HighlightValueColor);
	WeaponMesh->SetCustomDepthStencilValue(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CharacterTagID].HighlightValueColor);
}

void ACharacterBase::UnHighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
UCapsuleComponent* ACharacterBase::GetCapsule()
{
	return GetCapsuleComponent();
}

USkeletalMeshComponent* ACharacterBase::GetModelMesh()
{
	return GetMesh();
}

USkeletalMeshComponent* ACharacterBase::GetWeaponMesh()
{
	return WeaponMesh;
}
FTransform ACharacterBase::GetWeaponMechanicSocketTransform()
{
	return WeaponMesh->GetSocketTransform(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CharacterTagID].WeaponMechanicSocketName);
}
void ACharacterBase::TargetMotionWarping(FVector TargetLocation)
{
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(
		UAuraSubSystem::GetAuraSubSystem(this)->AuraData->DataPerCharacter[CharacterTagID].MotionWarpingTargetName,
		TargetLocation);
}
FGameplayTag ACharacterBase::GetCharacterID()
{
	return CharacterTagID;
}
FOnDeath& ACharacterBase::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

UDecalComponent* ACharacterBase::GetDecalComponent()
{
	return nullptr;
}

