// Mostafa Eldesouky


#include "UI/AuraHUD.h"

#include "Blueprint/UserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	
	BaseUserWidget = CreateWidget<UUserWidget>(GetWorld(), BaseUserWidgetClass);
	if (BaseUserWidget.IsValid()) BaseUserWidget.Get()->AddToViewport();
}
