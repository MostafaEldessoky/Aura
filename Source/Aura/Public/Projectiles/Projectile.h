// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class URotatingMovementComponent;
class UAbilitySystemComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class AURA_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();
	int32 AbilityLevel;
	float LifeTime{5.f};
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent; 
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingMovementComponent;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag CueTag;
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag DamageEffectTag;
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
