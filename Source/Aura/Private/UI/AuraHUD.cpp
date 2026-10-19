// Mostafa Eldesouky


#include "UI/AuraHUD.h"

#include "Blueprint/UserWidget.h"

bool AAuraHUD::IsUserWidgetValid()
{
	if (BaseUserWidget.IsValid())
		return true;
	return false;
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	
	BaseUserWidget = CreateWidget<UUserWidget>(GetWorld(), BaseUserWidgetClass);
	if (BaseUserWidget.IsValid()) 
		BaseUserWidget.Get()->AddToViewport();
}

