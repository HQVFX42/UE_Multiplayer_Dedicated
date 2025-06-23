// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portal/SignIn/SignUpPage.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void USignUpPage::NativeConstruct()
{
	Super::NativeConstruct();

	TextBox_Username->OnTextChanged.AddDynamic(this, &ThisClass::UpdateSignUpButtonState);
	TextBox_Password->OnTextChanged.AddDynamic(this, &ThisClass::UpdateSignUpButtonState);
	TextBox_ConfirmPassword->OnTextChanged.AddDynamic(this, &ThisClass::UpdateSignUpButtonState);
	TextBox_Email->OnTextChanged.AddDynamic(this, &ThisClass::UpdateSignUpButtonState);
}

void USignUpPage::UpdateSignUpButtonState(const FText& Text)
{
	const bool bIsUsernameValid = TextBox_Username->GetText().ToString().Len() >= 2;
	const bool bArePasswordsEqual = TextBox_Password->GetText().EqualTo(TextBox_ConfirmPassword->GetText());
	const bool bIsEmailValid = IsValidEmail(TextBox_Email->GetText().ToString());

	FString StatusMessage;
	const bool bIsStrongPassword = IsStrongPassword(TextBox_Password->GetText().ToString(), StatusMessage);
	if (!IsStrongPassword(TextBox_Password->GetText().ToString(), StatusMessage))
	{
		TextBlock_StatusMessage->SetText(FText::FromString(StatusMessage));
		TextBlock_StatusMessage->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!bIsUsernameValid)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Please enter at least two characters for Username.")));
		TextBlock_StatusMessage->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!bArePasswordsEqual)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Passwords do not match.")));
		TextBlock_StatusMessage->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!bIsEmailValid)
	{
		TextBlock_StatusMessage->SetText(FText::FromString(TEXT("Please enter a valid Email.")));
		TextBlock_StatusMessage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TextBlock_StatusMessage->SetVisibility(ESlateVisibility::Collapsed);
	}

	Button_SignUp->SetIsEnabled(bIsUsernameValid && bArePasswordsEqual && bIsEmailValid && bIsStrongPassword);
}

void USignUpPage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets)
{
	TextBlock_StatusMessage->SetText(FText::FromString(Message));
	if (bShouldResetWidgets)
	{
		Button_SignUp->SetIsEnabled(true);
	}
}

bool USignUpPage::IsValidEmail(const FString& Email)
{
	//"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
	const FRegexPattern EmailPattern(TEXT(R"(^[^\s@]+@[^\s@]+\.[^\s@]{2,}$)"));
	FRegexMatcher Matcher(EmailPattern, Email);
	return Matcher.FindNext();
}

bool USignUpPage::IsStrongPassword(const FString& InPassword, FString& OutStatusMessage)
{
	const FRegexPattern NumberPattern(TEXT(R"(\d)"));	// At least one number
	const FRegexPattern UppercasePattern(TEXT(R"([A-Z])"));	// At least one uppercase letter
	const FRegexPattern LowercasePattern(TEXT(R"([a-z])"));	// At least one lowercase letter
	const FRegexPattern SpecialCharPattern(TEXT(R"([^\w\s])"));	// At least one special character

	FRegexMatcher NumberMatcher(NumberPattern, InPassword);
	FRegexMatcher UppercaseMatcher(UppercasePattern, InPassword);
	FRegexMatcher LowercaseMatcher(LowercasePattern, InPassword);
	FRegexMatcher SpecialCharMatcher(SpecialCharPattern, InPassword);

	if (InPassword.Len() < 8)
	{
		OutStatusMessage = TEXT("Password must be at least 8 characters long.");
		return false;
	}
	if (!NumberMatcher.FindNext())
	{
		OutStatusMessage = TEXT("Password must contain at least one number.");
		return false;
	}
	if (!UppercaseMatcher.FindNext())
	{
		OutStatusMessage = TEXT("Password must contain at least one uppercase letter.");
		return false;
	}
	if (!LowercaseMatcher.FindNext())
	{
		OutStatusMessage = TEXT("Password must contain at least one lowercase letter.");
		return false;
	}
	if (!SpecialCharMatcher.FindNext())
	{
		OutStatusMessage = TEXT("Password must contain at least one special character.");
		return false;
	}
	OutStatusMessage = TEXT("Password is strong.");
	return true;
}
