// Mostafa Eldesouky


#include "UI/UserWidgets/SavingLoadingWidgets/LeaveGame.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void ULeaveGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LeaveGameButton->OnClicked.AddDynamic(this, &ULeaveGame::OnLeaveGameButtonClicked);
}

void ULeaveGame::OnLeaveGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
