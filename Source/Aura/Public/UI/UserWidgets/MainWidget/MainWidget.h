// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
private:
	UPROPERTY(Meta = (BindWidget))
	UUserWidget* AttributeWidget;
	bool bIsAttributeWidgetVisible{false};
	UPROPERTY(Meta = (BindWidget))
	UUserWidget* SpellTreeWidget;
	bool bIsSpellTreeWidgetVisible{false};
};
