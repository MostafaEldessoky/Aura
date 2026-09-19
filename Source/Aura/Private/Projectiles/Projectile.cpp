// Mostafa Eldesouky


#include "Projectiles/Projectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Statics/Utilities.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);
	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetEnableGravity(false);
	SphereComp->SetGenerateOverlapEvents(false);
	SphereComp->SetNotifyRigidBodyCollision(true);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->SetIsReplicated(true);
	bReplicates = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->SetCollisionProfileName(UUtilities::GetAuraSubSystem(this)->AuraData->ProjectileData.ProjectileProfileName);
	SphereComp->OnComponentHit.AddDynamic(this,&AProjectile::OnSphereHit);
	OwnedASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
}

void AProjectile::OnSphereHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner()) return;
	UGameplayStatics::PlaySoundAtLocation(
		this,
		UUtilities::GetAuraSubSystem(this)->AuraData->ProjectileData.ProjectileAssets[Tags::Projectiles::FireBall].HitSoundEffect,
		Hit.ImpactPoint);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		UUtilities::GetAuraSubSystem(this)->AuraData->ProjectileData.ProjectileAssets[Tags::Projectiles::FireBall].HitFXEffect,
		Hit.ImpactPoint);
	
	if (auto temp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		OwnedASC->ApplyGameplayEffectSpecToTarget(*ProjectileEffectSpecHandle.Data.Get(),temp);
	
	Destroy();
}
