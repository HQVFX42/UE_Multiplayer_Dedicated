#include "UI/HTTP/HTTPRequestTypes.h"
#include "DedicatedServers/DedicatedServers.h"

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