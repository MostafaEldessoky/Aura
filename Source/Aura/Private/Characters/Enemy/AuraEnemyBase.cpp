// Mostafa Eldesouky


#include "Characters/Enemy/AuraEnemyBase.h"

#include "AbilitySystem/AbilitySystemComponent/AuraASC.h"
#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "AI/AIController/AuraAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


AAuraEnemyBase::AAuraEnemyBase()
{
	AuraASC = CreateDefaultSubobject<UAuraASC>(TEXT("AuraASC"));
	AuraAttributes = CreateDefaultSubobject<UAuraAttributes>(TEXT("AuraAttributes"));
	AIControllerClass = AAuraAIController::StaticClass();
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

UAbilitySystemComponent* AAuraEnemyBase::GetAbilitySystemComponent() const
{
	return AuraASC.Get();
}
UAuraAttributes* AAuraEnemyBase::GetAuraAttributes() const
{
	return AuraAttributes.Get();
}

