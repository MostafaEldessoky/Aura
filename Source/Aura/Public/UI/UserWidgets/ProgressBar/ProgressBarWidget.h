// Mostafa Eldesouky

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ProgressBarInterface.h"
#include "StructUtils/InstancedStruct.h"
#include "ProgressBarWidget.generated.h"

class UProgressBar;

UENUM(BlueprintType)
enum class EProgressBarType : uint8
{
	NONE,
	WIDGETCOMPONENTBARS,
	LOCALPLAYERBARS,
	INPUTBARS,
	ABILITYBARS
};
UENUM(BlueprintType)
enum class EProgressBarAbilityState : uint8
{
	Locked,
	UnLocked,
	Equipped
};

USTRUCT(BlueprintType) struct FProgressBarData
{
	GENERATED_BODY()
	
	FProgressBarData() {}
	FProgressBarData(const FProgressBarData& Other) = default;
	FProgressBarData& operator=(const FProgressBarData& Other) = default;
	FProgressBarData(FProgressBarData&& Other) = default;
	FProgressBarData& operator=(FProgressBarData&& Other) = default;
	virtual ~FProgressBarData() {}
	
	UPROPERTY(EditAnywhere,Category=CPPVars)
	EProgressBarType Type;
};
USTRUCT(BlueprintType) struct FProgressBarAttributesData : public FProgressBarData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category=CPPVars)
	FGameplayAttribute Attribute;
	UPROPERTY(EditAnywhere,Category=CPPVars)
	FGameplayAttribute MaxAttribute;
};
USTRUCT(BlueprintType) struct FProgressBarAbilityData : public FProgressBarData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category=CPPVars)
	FGameplayTag AbilityTag;
	UPROPERTY(EditAnywhere,Category=CPPVars)
	UUserWidget* DefaultDragVisual;
};
USTRUCT(BlueprintType) struct FProgressBarInputData : public FProgressBarAbilityData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category=CPPVars)
	FGameplayTag InputTag;
};
/**
 * 
 */
UCLASS()
class AURA_API UProgressBarWidget : public UUserWidget, public IProgressBarInterface
{
	GENERATED_BODY()
public:
	virtual void SetActorName(FString Name)  override;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
private:
	UFUNCTION()
	void PressedMouseTimer();
	void SetCooldownPercent(float Duration);
	FTimerHandle PressedMouseTimerHandle;
	UPROPERTY(EditAnywhere,Category=CPPVars)
	FInstancedStruct InstanceStruct;
	bool bIsMouseEntered{false};
	bool bIsMouseButtonDown{false};
	float PressedMouseTimerDuration{0.f};
	float CurrentCooldownDuration{0};
	int8 CurrentRequirements{0};
	EProgressBarAbilityState AbilityState{EProgressBarAbilityState::Locked};
	int16 AbilityPoints{0};
	bool bIsTimerCalled{false};
	bool bCooldownBounded{false};
	float MaxAttributeAmount{1};
	FString ActorName;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
};
