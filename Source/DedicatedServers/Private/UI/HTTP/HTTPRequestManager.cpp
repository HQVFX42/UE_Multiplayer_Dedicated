// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HTTP/HTTPRequestManager.h"
#include "JsonObjectConverter.h"

#include "DedicatedServers/DedicatedServers.h"
#include "UI/HTTP/HTTPRequestTypes.h"

bool UHTTPRequestManager::ContainsErrors(TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject->HasField(TEXT("error")))
	{
		const TSharedPtr<FJsonObject>* ErrorObjectPtr;
		if (JsonObject->TryGetObjectField(TEXT("error"), ErrorObjectPtr))
		{
			const TSharedPtr<FJsonObject>& ErrorObject = *ErrorObjectPtr;
			FString ErrorType = ErrorObject->HasField(TEXT("name")) ? ErrorObject->GetStringField(TEXT("name")) : TEXT("Unknown Error");
			//FString ErrorMessage = ErrorObject->HasField(TEXT("$fault")) ? ErrorObject->GetStringField(TEXT("$fault")) : TEXT("Unknown Error Message");
			UE_LOG(LogDS, Error, TEXT("Error Type: %s"), *ErrorType);
			//UE_LOG(LogDS, Error, TEXT("Error Message: %s"), *ErrorMessage);

			return true;
		}
	}
	if (JsonObject->HasField(TEXT("errorType")) or JsonObject->HasField(TEXT("errorMessage")))
	{
		FString ErrorType = JsonObject->HasField(TEXT("errorType")) ? JsonObject->GetStringField(TEXT("errorType")) : TEXT("Unknown Error");
		FString ErrorMessage = JsonObject->HasField(TEXT("errorMessage")) ? JsonObject->GetStringField(TEXT("errorMessage")) : TEXT("Unknown Error Message");

		UE_LOG(LogDS, Error, TEXT("Error Type: %s"), *ErrorType);
		UE_LOG(LogDS, Error, TEXT("Error Message: %s"), *ErrorMessage);

		return true;
	}

	return false;
}

void UHTTPRequestManager::DumpMetaData(TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject->HasField(TEXT("$metadata")))
	{
		TSharedPtr<FJsonObject> MetaDataJsonObject = JsonObject->GetObjectField(TEXT("$metadata"));
		FDSMetaData DSMetaData;
		FJsonObjectConverter::JsonObjectToUStruct(MetaDataJsonObject.ToSharedRef(), &DSMetaData);

		DSMetaData.Dump();
	}
}

FString UHTTPRequestManager::SerializeJsonObject(const TMap<FString, FString>& Params)
{
	TSharedPtr<FJsonObject> ContentJsonObject = MakeShareable(new FJsonObject());
	
	for (const auto& Param : Params)
	{
		ContentJsonObject->SetStringField(Param.Key, Param.Value);
	}

	FString Content;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Content);
	FJsonSerializer::Serialize(ContentJsonObject.ToSharedRef(), JsonWriter);

	return Content;
}
