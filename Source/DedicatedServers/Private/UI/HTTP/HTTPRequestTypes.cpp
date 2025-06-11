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
