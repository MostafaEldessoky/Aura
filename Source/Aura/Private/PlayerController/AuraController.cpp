// Mostafa Eldesouky


#include "PlayerController/AuraController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Data/AuraData.h"
#include "Interfaces/Targetable.h"
#include "Statics/AuraSubSystem.h"
#include "Data/Tags.h"
#include "Statics/Utilities.h"

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
        	for ( const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->InputData.InputMappingContext)
        		if (temp.Key.MatchesTagExact(Tags::Inputs::MappingContexts::Default))
        			Subsystem->AddMappingContext(temp.Value,0);
        }
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	TraceUnderMouse();
}
void AAuraController::SetupInputComponent()
{
	Super::SetupInputComponent();
	auto ESC = Cast<UEnhancedInputComponent>(InputComponent);
	for (const auto& temp : UUtilities::GetAuraSubSystem(this)->AuraData->InputData.InputActions)
		ESC->BindActionValueLambda(temp.Value,ETriggerEvent::Started,[this,temp](const FInputActionValue& Value)
		{
			UUtilities::GetAuraSubSystem(this)->OnInputPressed.Broadcast(temp.Key);
		});
}
void AAuraController::TraceUnderMouse()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(UUtilities::GetAuraSubSystem(this)->AuraData->PlayerData.TraceChannel,false,HitResult);
	CurrentTarget = HitResult.GetActor();
	if (CurrentTarget)
	{
		CurrentTarget->Highlight();
		LastTarget = CurrentTarget;
		if (LastTarget && LastTarget != CurrentTarget)
			LastTarget->UnHighlight();
	}
	else if (LastTarget)
			LastTarget->UnHighlight();
	GetWorldTimerManager().SetTimerForNextTick([this]()
	{
		TraceUnderMouse();
	});
}
