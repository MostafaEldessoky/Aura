// Mostafa Eldesouky


#include "UI/UserWidgets/ProgressBar/ProgressBarWidget.h"

#include "AbilitySystem/Attribute/AuraAttributes.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Data/AuraData.h"
#include "Data/Tags.h"
#include "Statics/AuraSubSystem.h"

void UProgressBarWidget::SetActorName(FString Name) 
{
	ActorName = Name;
}
void UProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (!InstanceStruct.IsValid())
		return;
	auto type = InstanceStruct.Get<FProgressBarData>().Type;
	switch (type)
	{
		case EProgressBarType::LOCALPLAYERBARS :
			{
				auto temp = InstanceStruct.Get<FProgressBarAttributesData>();
				auto Attribute = temp.Attribute;
				auto MaxAttribute = temp.MaxAttribute;
				UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.AddLambda([this,Attribute,MaxAttribute](FString attributeName, float attributeAmount)
				{
					if (attributeName == MaxAttribute.GetName())
						MaxAttributeAmount = attributeAmount;
					else if (attributeName == Attribute.GetName())
						ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
				});
			}
			break;
		case EProgressBarType::WIDGETCOMPONENTBARS :
			{
				auto temp = InstanceStruct.Get<FProgressBarAttributesData>();
				auto Attribute = temp.Attribute;
				auto MaxAttribute = temp.MaxAttribute;
				UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedForWidgetComp.AddLambda([this,Attribute,MaxAttribute](FString ActorID,FString attributeName, float attributeAmount)
				{
					if (ActorName != ActorID)
						return;
					if (attributeName == MaxAttribute.GetName())
						MaxAttributeAmount = attributeAmount;
					else if (attributeName == Attribute.GetName())
						ProgressBar->SetPercent(attributeAmount/MaxAttributeAmount);
				});
			}
			break;
		case EProgressBarType::INPUTBARS :
			{
				auto temp = InstanceStruct.Get<FProgressBarInputData>();
				auto AbilityTag = temp.AbilityTag;
				if (! AbilityTag.IsValid()) 
					return;
				ProgressBar->SetPercent(1.f);
				ProgressBar->SetWidgetStyle(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIAbilitiesData[AbilityTag].AbilityImage);
				UAuraSubSystem::GetAuraSubSystem(this)->OnCooldownStart.AddLambda([this,AbilityTag](FGameplayTag Tag,float Duration)
				{
					if (!AbilityTag.IsValid() || !UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIAbilitiesData[AbilityTag].CooldownTag.MatchesTagExact(Tag))
						return;
						CurrentCooldownDuration = 0;
						SetCooldownPercent(Duration);
				});
			}
			break;
		case EProgressBarType::ABILITYBARS :
			{
				auto temp = InstanceStruct.Get<FProgressBarAbilityData>();
				ProgressBar->SetPercent(1.f);
				auto AbilityTag = temp.AbilityTag;
				auto Attribute = UAuraAttributes::GetXPAttribute();
				auto MaxAttribute = UAuraAttributes::GetMaxXPAttribute();
				FUIAbilitiesData UIAbilityData = UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIAbilitiesData[AbilityTag];
				ProgressBar->SetWidgetStyle(UIAbilityData.LockedImage);
				FGameplayTagContainer RequiresTagsToUnlock = UIAbilityData.RequiresTagsToUnlock;
				if (RequiresTagsToUnlock.Num() == 0)
				{
					ProgressBar->SetWidgetStyle(UIAbilityData.UnlockedImage);
					AbilityState = EProgressBarAbilityState::UnLocked;
				}
				UAuraSubSystem::GetAuraSubSystem(this)->OnGiveAbility.AddLambda([this,RequiresTagsToUnlock,UIAbilityData,AbilityTag](FGameplayTagContainer Container)
				{
					if (Container.HasTag(Aura::InputActions::InputActions) && Container.HasTagExact(AbilityTag))
					{
						ProgressBar->SetWidgetStyle(UIAbilityData.AbilityImage);
						AbilityState = EProgressBarAbilityState::Equipped;
					}
					if (Container.HasTag(Aura::Abilities::Abilities) && RequiresTagsToUnlock.HasAnyExact(Container))
					{
						CurrentRequirements++;
						if (RequiresTagsToUnlock.Num() == CurrentRequirements)
						{
							ProgressBar->SetWidgetStyle(UIAbilityData.UnlockedImage);
							AbilityState = EProgressBarAbilityState::UnLocked;
						}
					}
				});
				UAuraSubSystem::GetAuraSubSystem(this)->OnAttributeChangedPlayer.AddLambda([this,MaxAttribute,Attribute](FString attributeName, float attributeAmount)
				{
					if (attributeName == MaxAttribute.GetName())
						MaxAttributeAmount = attributeAmount;
					else if (attributeName == Attribute.GetName())
						AbilityPoints = attributeAmount/MaxAttributeAmount;
				});
			}
			break;
		default :
			break;
	}
}
void UProgressBarWidget::SetCooldownPercent(float Duration)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([this,Duration]()
	{
		if (CurrentCooldownDuration >= Duration)
			return;
		CurrentCooldownDuration += GetWorld()->GetDeltaSeconds();
		ProgressBar->SetPercent(CurrentCooldownDuration/Duration);
		SetCooldownPercent(Duration);
	});
}
void UProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bIsMouseEntered && bIsMouseButtonDown && !bIsTimerCalled && AbilityState >= EProgressBarAbilityState::UnLocked && AbilityPoints > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(PressedMouseTimerHandle,this,&UProgressBarWidget::PressedMouseTimer,2.0f,false);
		PressedMouseTimerDuration = 2.f;
		bIsTimerCalled = true;
	}
	else if (bIsMouseEntered && bIsMouseButtonDown && bIsTimerCalled)
	{
		PressedMouseTimerDuration -= InDeltaTime;
		ProgressBar->SetPercent(PressedMouseTimerDuration/2.0f);
	}
	else if ((!bIsMouseEntered || !bIsMouseButtonDown) && bIsTimerCalled)
	{
		bIsTimerCalled = false;
		ProgressBar->SetPercent(1.f);
	}
}
void UProgressBarWidget::PressedMouseTimer()
{
	if (!bIsTimerCalled)
		return;
	bIsTimerCalled = false;
	bIsMouseButtonDown = false;
	ProgressBar->SetPercent(1.f);
	if (!InstanceStruct.IsValid())
		return;
	
	FGameplayTag AbilityTag;
	EProgressBarType type = InstanceStruct.Get<FProgressBarData>().Type;
	if (type == EProgressBarType::INPUTBARS)
	{
		FProgressBarInputData temp = InstanceStruct.Get<FProgressBarInputData>();
		AbilityTag = temp.AbilityTag;
	}
	else if (type == EProgressBarType::ABILITYBARS)
	{
		FProgressBarAbilityData temp = InstanceStruct.Get<FProgressBarAbilityData>();
		AbilityTag = temp.AbilityTag;
	}
	if (AbilityState == EProgressBarAbilityState::UnLocked && AbilityPoints >  0.f )
	{
		UAuraSubSystem::GetAuraSubSystem(this)->OnUnlockAbility.Broadcast(AbilityTag);
		ProgressBar->SetWidgetStyle(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIAbilitiesData[AbilityTag].AbilityImage);
		AbilityState = EProgressBarAbilityState::Equipped;
	}
	else if (AbilityState == EProgressBarAbilityState::Equipped && AbilityPoints >  0.f )
		UAuraSubSystem::GetAuraSubSystem(this)->OnNeedLevelUpAbility.Broadcast(AbilityTag);
}
void UProgressBarWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	bIsMouseEntered = true;
}
void UProgressBarWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	bIsMouseEntered = false;
}
FReply UProgressBarWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		bIsMouseButtonDown = true;
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && InstanceStruct.Get<FProgressBarData>().Type >= EProgressBarType::INPUTBARS)
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton).NativeReply;
	return FReply::Handled();
}
FReply UProgressBarWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		bIsMouseButtonDown = false;
	return FReply::Handled();
}
void UProgressBarWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	OutOperation = NewObject<UDragDropOperation>(this, UDragDropOperation::StaticClass());
	if (!InstanceStruct.IsValid())
		return;
	
	if (InstanceStruct.Get<FProgressBarData>().Type == EProgressBarType::INPUTBARS)
	{
		auto temp = InstanceStruct.GetMutablePtr<FProgressBarInputData>();
		OutOperation->Tag = temp->AbilityTag.ToString();
		OutOperation->DefaultDragVisual = temp->DefaultDragVisual;
		temp->AbilityTag = FGameplayTag();
		auto style = FProgressBarStyle::GetDefault();
		style.BackgroundImage.TintColor = FLinearColor(1,1,1,0);
		style.FillImage.TintColor = FLinearColor(1,1,1,0);
		ProgressBar->SetWidgetStyle(style);
		FGameplayTagContainer Container;
		Container.AddTag(FGameplayTag::RequestGameplayTag(FName(OutOperation->Tag)));
		UAuraSubSystem::GetAuraSubSystem(this)->OnAssignAbilityToInput.Broadcast(Container);
	}
	else if (InstanceStruct.Get<FProgressBarData>().Type == EProgressBarType::ABILITYBARS)
	{
		FProgressBarAbilityData temp = InstanceStruct.Get<FProgressBarAbilityData>();
		OutOperation->Tag = temp.AbilityTag.ToString();
		OutOperation->DefaultDragVisual = temp.DefaultDragVisual;
	}
}
bool UProgressBarWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (InstanceStruct.Get<FProgressBarData>().Type == EProgressBarType::INPUTBARS && InDragDropEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		auto temp = InstanceStruct.GetMutablePtr<FProgressBarInputData>();
		temp->AbilityTag = FGameplayTag::RequestGameplayTag(FName(InOperation->Tag));
		FGameplayTagContainer Container;
		Container.AddTag(temp->AbilityTag);
		Container.AddTag(temp->InputTag);
		UAuraSubSystem::GetAuraSubSystem(this)->OnAssignAbilityToInput.Broadcast(Container);
		InOperation->DefaultDragVisual = nullptr;
		if (!bCooldownBounded)
		{
			bCooldownBounded = true;
			UAuraSubSystem::GetAuraSubSystem(this)->OnCooldownStart.AddLambda([this,temp](FGameplayTag Tag,float Duration)
			{
				if (!temp->AbilityTag.IsValid() || !UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIAbilitiesData[temp->AbilityTag].CooldownTag.MatchesTagExact(Tag))
					return;
					CurrentCooldownDuration = 0;
					SetCooldownPercent(Duration);
			});
		}
		ProgressBar->SetWidgetStyle(UAuraSubSystem::GetAuraSubSystem(this)->AuraData->UIAbilitiesData[temp->AbilityTag].AbilityImage);
		ProgressBar->SetPercent(1.f);
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
