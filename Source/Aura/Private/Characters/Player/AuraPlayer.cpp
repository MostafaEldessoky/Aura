// Mostafa Eldesouky


#include "Characters/Player/AuraPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerState/AuraState.h"
#include "Statics/AuraFunctionLibrary.h"


AAuraPlayer::AAuraPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("DecalCompInstance");
	DecalComponent->SetVisibility(false);
	DecalComponent->Deactivate();
}
void AAuraPlayer::BeginPlay()
{
	Super::BeginPlay();
	UAuraFunctionLibrary::TickFuncUntil(this,[this](){return Cast<AAuraState>(GetPlayerState()) != nullptr;},[this]()
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
FGenericTeamId AAuraPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(1);
}

UDecalComponent* AAuraPlayer::GetDecalComponent()
{
	return DecalComponent;
}
