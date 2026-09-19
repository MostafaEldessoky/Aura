// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class AURA_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();
	FGameplayEffectSpecHandle ProjectileEffectSpecHandle;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent; 
	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	TWeakObjectPtr<UAbilitySystemComponent> OwnedASC;
};
