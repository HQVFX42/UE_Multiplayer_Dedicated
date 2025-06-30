#include "UI/HTTP/HTTPRequestTypes.h"
#include "DedicatedServers/DedicatedServers.h"

namespace HTTPStatusMessages
{
	const FString SomethingWentWrong = TEXT("Something went wrong. Please try again later.");
}

void FDSMetaData::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("FDSMetaData:"));
	UE_LOG(LogDS, Log, TEXT("  httpStatusCode: %d"), httpStatusCode);
	UE_LOG(LogDS, Log, TEXT("  requestId: %s"), *requestId);
	UE_LOG(LogDS, Log, TEXT("  attempts: %d"), attempts);
	UE_LOG(LogDS, Log, TEXT("  totalRetryDelay: %f"), totalRetryDelay);
}

void FDSListFleetsResponse::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("FDSListFleetsResponse:"));
	for (const FString& FleetId : FleetIds)
	{
		UE_LOG(LogDS, Log, TEXT("  FleetId: %s"), *FleetId);
	}
	if (!NextToken.IsEmpty())
	{
		UE_LOG(LogDS, Log, TEXT("  NextToken: %s"), *NextToken);
	}
	else
	{
		UE_LOG(LogDS, Log, TEXT("  NextToken: <empty>"));
	}
}

void FDSGameSession::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("FDSGameSession:"));
	UE_LOG(LogDS, Log, TEXT("  CreationTime: %s"), *CreationTime);
	UE_LOG(LogDS, Log, TEXT("  CreatorId: %s"), *CreatorId);
	UE_LOG(LogDS, Log, TEXT("  CurrentPlayerSessionCount: %d"), CurrentPlayerSessionCount);
	UE_LOG(LogDS, Log, TEXT("  DnsName: %s"), *DnsName);
	UE_LOG(LogDS, Log, TEXT("  FleetArn: %s"), *FleetArn);
	UE_LOG(LogDS, Log, TEXT("  FleetId: %s"), *FleetId);

	UE_LOG(LogDS, Log, TEXT("  GameProperties:"));
	for (const auto& GameProperty : GameProperties)
	{
		UE_LOG(LogDS, Log, TEXT("    %s: %s"), *GameProperty.Key, *GameProperty.Value);
	}

	UE_LOG(LogDS, Log, TEXT("  GameSessionData: %s"), *GameSessionData);
	UE_LOG(LogDS, Log, TEXT("  GameSessionId: %s"), *GameSessionId);
	UE_LOG(LogDS, Log, TEXT("  IpAddress: %s"), *IpAddress);
	UE_LOG(LogDS, Log, TEXT("  Location: %s"), *Location);
	UE_LOG(LogDS, Log, TEXT("  MatchmakerData: %s"), *MatchmakerData);
	UE_LOG(LogDS, Log, TEXT("  MaximumPlayerSessionCount: %d"), MaximumPlayerSessionCount);
	UE_LOG(LogDS, Log, TEXT("  Name: %s"), *Name);
	UE_LOG(LogDS, Log, TEXT("  PlayerSessionCreationPolicy: %s"), *PlayerSessionCreationPolicy);
	UE_LOG(LogDS, Log, TEXT("  Port: %d"), Port);
	UE_LOG(LogDS, Log, TEXT("  Status: %s"), *Status);
	UE_LOG(LogDS, Log, TEXT("  StatusReason: %s"), *StatusReason);
	UE_LOG(LogDS, Log, TEXT("  TerminationTime: %s"), *TerminationTime);
}

void FDSPlayerSession::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("PlayerSession:"));
	UE_LOG(LogDS, Log, TEXT("  CreationTime: %s"), *CreationTime);
	UE_LOG(LogDS, Log, TEXT("  DnsName: %s"), *DnsName);
	UE_LOG(LogDS, Log, TEXT("  FleetArn: %s"), *FleetArn);
	UE_LOG(LogDS, Log, TEXT("  FleetId: %s"), *FleetId);
	UE_LOG(LogDS, Log, TEXT("  GameSessionId: %s"), *GameSessionId);
	UE_LOG(LogDS, Log, TEXT("  IpAddress: %s"), *IpAddress);
	UE_LOG(LogDS, Log, TEXT("  PlayerData: %s"), *PlayerData);
	UE_LOG(LogDS, Log, TEXT("  PlayerId: %s"), *PlayerId);
	UE_LOG(LogDS, Log, TEXT("  PlayerSessionId: %s"), *PlayerSessionId);
	UE_LOG(LogDS, Log, TEXT("  Port: %d"), Port);
	UE_LOG(LogDS, Log, TEXT("  Status: %s"), *Status);
	UE_LOG(LogDS, Log, TEXT("  TerminationTime: %s"), *TerminationTime);
}

void FDSCodeDeliveryDetails::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("CodeDeliveryDetails:"));
	UE_LOG(LogDS, Log, TEXT("   AttributeName: %s"), *AttributeName);
	UE_LOG(LogDS, Log, TEXT("   DeliveryMedium: %s"), *DeliveryMedium);
	UE_LOG(LogDS, Log, TEXT("   Destination: %s"), *Destination);
}

void FDSSignUpResponse::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("FDSSignUpResponse Details:"));
	CodeDeliveryDetails.Dump();
	UE_LOG(LogDS, Log, TEXT("UserConfirmed: %s"), UserConfirmed ? TEXT("true") : TEXT("false"));
	UE_LOG(LogDS, Log, TEXT("UserSub: %s"), *UserSub);
}

void FDSNewDeviceMetaData::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("NewDeviceMetadata:"));
	UE_LOG(LogDS, Log, TEXT("   DeviceGroupKey: %s"), *DeviceGroupKey);
	UE_LOG(LogDS, Log, TEXT("   DeviceKey: %s"), *DeviceKey);
}

void FDSAuthenticationResult::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("AuthenticationResult:"));
	UE_LOG(LogDS, Log, TEXT("   AccessToken: %s"), *AccessToken);
	UE_LOG(LogDS, Log, TEXT("   ExpiresIn: %d"), ExpiresIn);
	UE_LOG(LogDS, Log, TEXT("   IdToken: %s"), *IdToken);
	NewDeviceMetadata.Dump();
	UE_LOG(LogDS, Log, TEXT("   RefreshToken: %s"), *RefreshToken);
	UE_LOG(LogDS, Log, TEXT("   TokenType: %s"), *TokenType);
}

void FDSChallengeParameters::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("ChallengeParameters:"));
	for (const auto& Param : Parameters)
	{
		UE_LOG(LogDS, Log, TEXT("   %s: %s"), *Param.Key, *Param.Value);
	}
}

void FDSInitiateAuthResponse::Dump() const
{
	UE_LOG(LogDS, Log, TEXT("FDSSignUpResponse Details:"));
	AuthenticationResult.Dump();
	UE_LOG(LogDS, Log, TEXT("ChallengeName: %s"), *ChallengeName);
	ChallengeParameters.Dump();
	UE_LOG(LogDS, Log, TEXT("Session: %s"), *Session);
}