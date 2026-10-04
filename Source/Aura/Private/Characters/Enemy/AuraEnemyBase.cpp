// Mostafa Eldesouky


#include "Characters/Enemy/AuraEnemyBase.h"

#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "AI/AIController/AuraAIController.h"
#include "Components/WidgetComponent.h"
#include "Data/AuraData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Statics/AuraSubSystem.h"
#include "Statics/AuraFunctionLibrary.h"
#include "UI/UserWidgets/ProgressBar/ProgressBarWidget.h"


AAuraEnemyBase::AAuraEnemyBase()
{
	AuraASC = CreateDefaultSubobject<UAuraASC>(TEXT("AuraASC"));
	AuraAttributes = CreateDefaultSubobject<UAuraAttributes>(TEXT("AuraAttributes"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
	AIControllerClass = AAuraAIController::StaticClass();
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

