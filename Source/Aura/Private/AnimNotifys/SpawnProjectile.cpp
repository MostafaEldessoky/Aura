// Mostafa Eldesouky


#include "AnimNotifys/SpawnProjectile.h"
#include "Data/Tags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void USpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp->GetOwner()->HasAuthority())
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),Tags::EventTasks::SpawnProjectile,FGameplayEventData());
}
