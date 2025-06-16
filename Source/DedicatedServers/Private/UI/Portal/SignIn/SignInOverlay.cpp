// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/SignInOverlay.h"
#include "Components/Button.h"

#include "UI/Portal/PortalManager.h"
#include "UI/API/GameSessions/JoinGame.h"

void USignInOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	check(PortalManagerClass);
	check(IsValid(JoinGameWidget));
	check(IsValid(JoinGameWidget->Button_JoinGame));

	PortalManager = NewObject<UPortalManager>(this, PortalManagerClass);

	JoinGameWidget->Button_JoinGame->OnClicked.AddDynamic(this, &ThisClass::OnJoinGameButtonClicked);
}

void USignInOverlay::OnJoinGameButtonClicked()
{
	check(IsValid(PortalManager));
	check(IsValid(JoinGameWidget));
	check(IsValid(JoinGameWidget->Button_JoinGame));

	PortalManager->BroadcastJoinGameSessionMessage.AddDynamic(this, &ThisClass::UpdateJoinGameSatusMessage);
	PortalManager->JoinGameSession();

	JoinGameWidget->Button_JoinGame->SetIsEnabled(false);
}

void USignInOverlay::UpdateJoinGameSatusMessage(const FString& StatusMessage, bool bResetJoinGameButton)
{
	check(IsValid(JoinGameWidget));
	check(IsValid(JoinGameWidget->Button_JoinGame));

	JoinGameWidget->SetStatusMessage(StatusMessage);

	if (bResetJoinGameButton)
	{
		JoinGameWidget->Button_JoinGame->SetIsEnabled(true);
	}
}
