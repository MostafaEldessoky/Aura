// Mostafa Eldesouky


#include "AbilitySystem/Cues/ElectrocuteCue.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


AElectrocuteCue::AElectrocuteCue()
{
	PrimaryActorTick.bCanEverTick = false;
	bAutoDestroyOnRemove = true;
}
bool AElectrocuteCue::WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	for (auto& temp : Parameters.EffectContext.Get()->GetActors())
		if (temp.IsValid())
			BeamPoints.Add(temp.Get()->GetActorLocation());
	auto temp1 = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BeamNiagara, Parameters.EffectContext.GetOrigin());
	temp1->SetNiagaraVariableVec3(TEXT("BeamStart"), Parameters.EffectContext.GetOrigin());
	BeamNiagaraComponents.Add(temp1);
	auto temp2 = 	UGameplayStatics::SpawnSoundAtLocation(this, MediaSound, Parameters.EffectContext.GetOrigin());
	BeamSoundComponents.Add(temp2);
	for (int32 i = 0; i < BeamPoints.Num(); i++)
	{
		BeamNiagaraComponents[i]->SetNiagaraVariableVec3(TEXT("Beam End"), BeamPoints[i]);
		if (i != BeamPoints.Num()-1)
		{
			temp1 = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BeamNiagara, BeamPoints[i]);
			temp1->SetNiagaraVariableVec3(TEXT("BeamStart"), BeamPoints[i]);
			BeamNiagaraComponents.Add(temp1);
		}
		temp2 = UGameplayStatics::SpawnSoundAtLocation(this, MediaSound, BeamPoints[i]);
		BeamSoundComponents.Add(temp2);
	}
	return Super::WhileActive_Implementation(MyTarget, Parameters);
}
bool AElectrocuteCue::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	BeamPoints.Empty();
	for (auto& temp1 : BeamNiagaraComponents)
	{
		temp1->Deactivate();
		temp1->DestroyComponent();
	}
	for (auto& temp2 : BeamSoundComponents)
	{
		temp2->Stop();
		temp2->DestroyComponent();
	}
	BeamNiagaraComponents.Empty();
	BeamSoundComponents.Empty();
	return Super::OnRemove_Implementation(MyTarget, Parameters);
}
