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