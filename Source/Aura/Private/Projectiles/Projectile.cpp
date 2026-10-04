// Mostafa Eldesouky


#include "Projectiles/Projectile.h"
#include "Components/SphereComponent.h"
#include "Data/AuraData.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Statics/AuraFunctionLibrary.h"
#include "Statics/AuraSubSystem.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);
	SphereComp->SetGenerateOverlapEvents(true);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	bNetLoadOnClient = true;
	bReplicates = true;
	SetReplicatingMovement(true);
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
	RotatingMovementComponent->RotationRate = FRotator(50.f,500.f,50.f);
	RotatingMovementComponent->PivotTranslation = FVector(25.f,100.f,0.f);
}
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
	SphereComp->SetCollisionProfileName(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.ProjectileProfileName);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::OnSphereBeginOverlap);
}
void AProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == GetOwner()) return;
	UAuraFunctionLibrary::ApplyEffectToTargetWithCue_NonReplicated(GetOwner(),OtherActor,SweepResult.ImpactPoint,CueTag,DamageEffectTag,AbilityLevel);
	Destroy();
}
