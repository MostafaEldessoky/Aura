// Mostafa Eldesouky


#include "AI/AIController/AuraAIController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/Tags.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"


AAuraAIController::AAuraAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1700.f;
	SightConfig->PeripheralVisionAngleDegrees = 75.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("HearingConfig");
	HearingConfig->HearingRange = 1200.f;
	HearingConfig->SetMaxAge(5.f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;
	
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>("DamageConfig");
	DamageConfig->SetMaxAge(5.f);
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->ConfigureSense(*HearingConfig);
	PerceptionComponent->ConfigureSense(*DamageConfig);
}
FGenericTeamId AAuraAIController::GetGenericTeamId() const
{
	return FGenericTeamId(2);
}
void AAuraAIController::BeginPlay()
{
	Super::BeginPlay();
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAuraAIController::OnTargetPerceptionUpdated);
	PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AAuraAIController::OnTargetPerceptionForgotten);
}
void AAuraAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		FGameplayEventData Payload;
		Payload.Target = Actor;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(),Aura::Tasks::AISenseTarget,Payload);
	}
}
void AAuraAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	FGameplayEventData Payload;
	Payload.Target = Actor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(),Aura::Tasks::AIForgotTarget,Payload);
}
