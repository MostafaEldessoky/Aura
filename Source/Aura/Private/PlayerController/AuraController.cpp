// Mostafa Eldesouky


#include "PlayerController/AuraController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Data/AuraData.h"
#include "Statics/AuraSubSystem.h"
#include "Data/Tags.h"
#include "Interfaces/Combat.h"

AAuraController::AAuraController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}
void AAuraController::BeginPlay()
{
	Super::BeginPlay();
	if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
        	for ( const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->InputData.InputMappingContext)
        		if (temp.Key.MatchesTagExact(Aura::InputMappingContexts::Default))
        			Subsystem->AddMappingContext(temp.Value,0);
        }
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
void AAuraController::SetupInputComponent()
{
	Super::SetupInputComponent();
	auto ESC = Cast<UEnhancedInputComponent>(InputComponent);
	for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->InputData.InputActions)
		ESC->BindActionValueLambda(temp.Value,ETriggerEvent::Started,[this,temp](const FInputActionValue& Value)
		{
			if (temp.Key.MatchesTagExact(Aura::UI::ToggleAttributeWidgets))
			{
				UAuraSubSystem::GetAuraSubSystem(this)->OnToggleAttributeWidget.Broadcast();
			}
			else if (temp.Key.MatchesTagExact(Aura::UI::ToggleSpellTreeWidgets))
			{
				UAuraSubSystem::GetAuraSubSystem(this)->OnToggleSpellTreeWidget.Broadcast();
			}
			else if (temp.Key.MatchesTagExact(Aura::UI::ToggleInGameMenuWidgets))
			{
				UAuraSubSystem::GetAuraSubSystem(this)->OnToggleInGameMenuWidget.Broadcast();
			}
			else if (temp.Key.MatchesTagExact(Aura::InputActions::RMB))
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(),temp.Key,FGameplayEventData());
			else 
				UAuraSubSystem::GetAuraSubSystem(this)->OnInputPressed.Broadcast(temp.Key);
		});
	for (const auto& temp : UAuraSubSystem::GetAuraSubSystem(this)->AuraData->InputData.InputActions)
		ESC->BindActionValueLambda(temp.Value,ETriggerEvent::Completed,[this,temp](const FInputActionValue& Value)
		{
			UAuraSubSystem::GetAuraSubSystem(this)->OnInputReleased.Broadcast(temp.Key);
		});
}
