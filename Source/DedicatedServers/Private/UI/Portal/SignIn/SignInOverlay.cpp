// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/SignInOverlay.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

#include "UI/Portal/PortalManager.h"
#include "UI/Portal/SignIn/SignInPage.h"
#include "UI/Portal/SignIn/SignUpPage.h"
#include "UI/Portal/SignIn/ConfirmSignUpPage.h"
#include "UI/Portal/SignIn/SuccessConfirmedPage.h"
#include "UI/API/GameSessions/JoinGame.h"

void USignInOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	check(PortalManagerClass);
	//check(IsValid(JoinGameWidget));
	//check(IsValid(JoinGameWidget->Button_JoinGame));

	PortalManager = NewObject<UPortalManager>(this, PortalManagerClass);

	JoinGameWidget->Button_JoinGame->OnClicked.AddDynamic(this, &ThisClass::OnJoinGameButtonClicked);

	Button_SignIn_Test->OnClicked.AddDynamic(this, &ThisClass::ShowSignInPage);
	Button_SignUp_Test->OnClicked.AddDynamic(this, &ThisClass::ShowSignUpPage);
	Button_ConfirmSignUp_Test->OnClicked.AddDynamic(this, &ThisClass::ShowConfirmSignUpPage);
	Button_SuccessConfirmed_Test->OnClicked.AddDynamic(this, &ThisClass::ShowSuccessConfirmedPage);

	//check(IsValid(SignInPage));
	//check(IsValid(SignInPage->Button_SignIn));
	SignInPage->Button_SignIn->OnClicked.AddDynamic(this, &ThisClass::SignInButtonClicked);
	SignInPage->Button_SignUp->OnClicked.AddDynamic(this, &ThisClass::ShowSignUpPage);
	SignInPage->Button_Quit->OnClicked.AddDynamic(PortalManager, &UPortalManager::QuitGame);

	//check(IsValid(SignUpPage));
	//check(IsValid(SignUpPage->Button_Back));
	//check(IsValid(SignUpPage->Button_SignUp));
	SignUpPage->Button_Back->OnClicked.AddDynamic(this, &ThisClass::ShowSignInPage);
	SignUpPage->Button_SignUp->OnClicked.AddDynamic(this, &ThisClass::SignUpButtonClicked);

	//check(IsValid(ConfirmSignUpPage));
	//check(IsValid(ConfirmSignUpPage->Button_Confirm));
	//check(IsValid(ConfirmSignUpPage->Button_Back));
	ConfirmSignUpPage->Button_Confirm->OnClicked.AddDynamic(this, &ThisClass::ConfirmButtonClicked);
	ConfirmSignUpPage->Button_Back->OnClicked.AddDynamic(this, &ThisClass::ShowSignUpPage);

	//check(IsValid(SuccessConfirmedPage));
	//check(IsValid(SuccessConfirmedPage->Button_Ok));
	SuccessConfirmedPage->Button_Ok->OnClicked.AddDynamic(this, &ThisClass::ShowSignInPage);
}

void USignInOverlay::OnJoinGameButtonClicked()
{
	PortalManager->BroadcastJoinGameSessionMessage.AddDynamic(this, &ThisClass::UpdateJoinGameSatusMessage);
	PortalManager->JoinGameSession();

	JoinGameWidget->Button_JoinGame->SetIsEnabled(false);
}

void USignInOverlay::UpdateJoinGameSatusMessage(const FString& StatusMessage, bool bResetJoinGameButton)
{
	JoinGameWidget->SetStatusMessage(StatusMessage);

	if (bResetJoinGameButton)
	{
		JoinGameWidget->Button_JoinGame->SetIsEnabled(true);
	}
}

void USignInOverlay::ShowSignInPage()
{
	WidgetSwitcher->SetActiveWidget(SignInPage);
}

void USignInOverlay::ShowSignUpPage()
{
	WidgetSwitcher->SetActiveWidget(SignUpPage);
}

void USignInOverlay::ShowConfirmSignUpPage()
{
	WidgetSwitcher->SetActiveWidget(ConfirmSignUpPage);
}

void USignInOverlay::ShowSuccessConfirmedPage()
{
	WidgetSwitcher->SetActiveWidget(SuccessConfirmedPage);
}

void USignInOverlay::SignInButtonClicked()
{
	const FString Username = SignInPage->TextBox_Username->GetText().ToString();
	const FString Password = SignInPage->TextBox_Password->GetText().ToString();
	PortalManager->SignIn(Username, Password);
}

void USignInOverlay::SignUpButtonClicked()
{
	const FString Username = SignUpPage->TextBox_Username->GetText().ToString();
	const FString Password = SignUpPage->TextBox_Password->GetText().ToString();
	const FString Email = SignUpPage->TextBox_Email->GetText().ToString();
	PortalManager->SignUp(Username, Password, Email);
}

void USignInOverlay::ConfirmButtonClicked()
{
	const FString ConfirmationCode = ConfirmSignUpPage->TextBox_ConfirmationCode->GetText().ToString();
	PortalManager->Confirm(ConfirmationCode);
}
