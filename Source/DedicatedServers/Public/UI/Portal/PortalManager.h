// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"

#include "UI/HTTP/HTTPRequestManager.h"

#include "PortalManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBroadcastJoinGameSessionMessage, const FString&, StatusMessage, bool, bShouldResetJoinGameButton);

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UPortalManager : public UHTTPRequestManager
{
	GENERATED_BODY()	
	
public:

	void JoinGameSession();
	void SignIn(const FString& Username, const FString& Password);
	void SignUp(const FString& Username, const FString& Password, const FString& Email);
	void Confirm(const FString& ConfirmationCode);

	UFUNCTION()
	void QuitGame();

	UPROPERTY(BlueprintAssignable)
	FBroadcastJoinGameSessionMessage BroadcastJoinGameSessionMessage;
	
private:
	void FindOrCreateGameSession_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void CreatePlayerSession_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString GetUniquePlayerId() const;
	void HandleGameSesionStatus(const FString& Status, const FString& SessionId);
	void TryCreatePlayerSession(const FString& PlayerId, const FString& GameSessionId);

	FTimerHandle CreateSessionTimer;
};
