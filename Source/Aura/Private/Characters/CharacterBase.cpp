// Mostafa Eldesouky


#include "Characters/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Data/AuraData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/Utilities.h"


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
}
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	WeaponMesh->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.WeaponMeshSocketName);
	WeaponMesh->SetCollisionProfileName(UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.WeaponCollisionProfileName);
	GetMesh()->SetCollisionProfileName(UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.MeshCollisionProfileName);
	GetCapsuleComponent()->SetCollisionProfileName(UUtilities::GetAuraSubSystem(this)->AuraData->CharacterBaseData.CapsuleCollisionProfileName);
}
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

UAuraAttributes* ACharacterBase::GetAuraAttributes() const
{
	return nullptr;
}

