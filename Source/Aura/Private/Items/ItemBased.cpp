// Mostafa Eldesouky


#include "Items/ItemBased.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"


AItemBased::AItemBased()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
}
void AItemBased::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->SetCollisionProfileName(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->CollisionsData.ItemCollisionProfileName);
	for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->ItemsData)
		if (temp.ItemEffect.MatchesTagExact(ItemTag))
		{
			EffectClass = UAuraSubSystem::GetAuraSubSystem(this)->AuraData->EffectsClasses[temp.ItemEffect];
			EffectLevel = temp.ItemLevel;
			break;
		}
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBased::OnBoxOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AItemBased::OnBoxEndOverlap);
}
void AItemBased::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto temp1 = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (!temp1) return;
	auto temp2 = temp1->MakeEffectContext();
	temp2.AddSourceObject(temp1);
	auto temp3 = temp1->MakeOutgoingSpec(EffectClass, EffectLevel, temp2);
	auto temp4 = temp1->ApplyGameplayEffectSpecToSelf(*temp3.Data.Get());
	if (temp3.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		ActiveEffectHandle.Add(temp4);
	else Destroy();
}
void AItemBased::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto temp1 = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (!temp1) return;
	for (auto& temp2 : ActiveEffectHandle)
		if ( temp1 == temp2.GetOwningAbilitySystemComponent())
			temp2.GetOwningAbilitySystemComponent()->RemoveActiveGameplayEffect(temp2,1);
}
