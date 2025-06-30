// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignUpPage.generated.h"

class UEditableTextBox;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API USignUpPage : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void UpdateSignUpButtonState(const FText& Text);

	bool IsValidEmail(const FString& Email);
	bool IsStrongPassword(const FString& Password, FString& StatusMessage);

protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
	void UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets);

	void ClearTextBoxes();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> TextBox_Username;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> TextBox_Password;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> TextBox_ConfirmPassword;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> TextBox_Email;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_SignUp;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_StatusMessage;
};
