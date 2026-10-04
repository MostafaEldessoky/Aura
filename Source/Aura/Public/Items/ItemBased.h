// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "ItemBased.generated.h"


class UGameplayEffect;
class UBoxComponent;

UCLASS()
class AURA_API AItemBased : public AActor
{
	GENERATED_BODY()

public:
	AItemBased();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly,Category=CPPVars)
	FGameplayTag ItemTag;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	TArray<FActiveGameplayEffectHandle> ActiveEffectHandle;
	TSubclassOf<UGameplayEffect> EffectClass;
	float EffectLevel;
};
