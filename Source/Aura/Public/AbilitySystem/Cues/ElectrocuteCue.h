// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "ElectrocuteCue.generated.h"

class UMediaSoundComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class AURA_API AElectrocuteCue : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	AElectrocuteCue();
	virtual bool WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
private:
	TArray<FVector> BeamPoints;
	UPROPERTY()
	TArray<UNiagaraComponent*> BeamNiagaraComponents;
	UPROPERTY()
	TArray<UAudioComponent*> BeamSoundComponents;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* BeamNiagara;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* MediaSound;
};
