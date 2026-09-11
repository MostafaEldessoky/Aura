// Mostafa Eldesouky


#include "Items/ItemBased.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/Utilities.h"


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
	BoxComponent->SetCollisionProfileName(UUtilities::GetAuraSubSystem(this)->AuraData->ItemData.BoxCollisionProfileName);
	for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->ItemData.ItemsEffect)
		if (temp.ItemTag.MatchesTagExact(ItemTag))
		{
			GamePlayEffectClass = temp.GamePlayEffectClass;
			EffectLevel = temp.EffectLevel;
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
	auto temp3 = temp1->MakeOutgoingSpec(GamePlayEffectClass, EffectLevel, temp2);
	auto temp4 = temp1->ApplyGameplayEffectSpecToSelf(*temp3.Data.Get());
	if (temp3.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		ActiveGameplayEffectHandle.Add(temp4);
	else Destroy();
}
void AItemBased::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto temp1 = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (!temp1) return;
	for (auto& temp2 : ActiveGameplayEffectHandle)
		if ( temp1 == temp2.GetOwningAbilitySystemComponent())
			temp2.GetOwningAbilitySystemComponent()->RemoveActiveGameplayEffect(temp2,1);
}
