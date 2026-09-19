// Mostafa Eldesouky


#include "Characters/Enemy/AuraEnemyBase.h"

#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Components/WidgetComponent.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/Utilities.h"
#include "UI/UserWidgets/ProgressBar/ProgressBarWidget.h"


AAuraEnemyBase::AAuraEnemyBase()
{
	AuraASC = CreateDefaultSubobject<UAuraASC>(TEXT("AuraASC"));
	AuraAttributes = CreateDefaultSubobject<UAuraAttributes>(TEXT("AuraAttributes"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void AAuraEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Cast<UProgressBarWidget>(WidgetComponent->GetUserWidgetObject())->EnemyName = GetName();
}

UAbilitySystemComponent* AAuraEnemyBase::GetAbilitySystemComponent() const
{
	return AuraASC.Get();
}
UAuraAttributes* AAuraEnemyBase::GetAuraAttributes() const
{
	return AuraAttributes.Get();
}
void AAuraEnemyBase::Highlight()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMesh->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(UUtilities::GetAuraSubSystem(this)->AuraData->EnemyData.HighlightValueColor);
	WeaponMesh->SetCustomDepthStencilValue(UUtilities::GetAuraSubSystem(this)->AuraData->EnemyData.HighlightValueColor);
}
void AAuraEnemyBase::UnHighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
