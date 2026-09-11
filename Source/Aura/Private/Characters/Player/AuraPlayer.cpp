// Mostafa Eldesouky


#include "Characters/Player/AuraPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerState/AuraState.h"
#include "Statics/Utilities.h"

AAuraPlayer::AAuraPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}
void AAuraPlayer::BeginPlay()
{
	Super::BeginPlay();
	UUtilities::Initialize(this,[this](){return Cast<AAuraState>(GetPlayerState()) != nullptr;},[this]()
	{
		AbilitySystemComponent = Cast<AAuraState>(GetPlayerState())->GetAbilitySystemComponent();
		AuraAttributes = Cast<AAuraState>(GetPlayerState())->GetAuraAttributes();
	});
}
UAbilitySystemComponent* AAuraPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
UAuraAttributes* AAuraPlayer::GetAuraAttributes() const
{
	return AuraAttributes;
}

