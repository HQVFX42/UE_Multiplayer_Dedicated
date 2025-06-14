// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/APITest/APITestManager.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"

#include "UI/HTTP/HTTPRequestTypes.h"
#include "Data/API/APIData.h"
#include "DedicatedServers/DedicatedServers.h"

void UAPITestManager::ListFleetsButtonClicked()
{
	check(APIData);

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	
	Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::ListFleets_Response);
	
	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::GameSessionsAPI::ListFleets);
	
	Request->SetURL(APIUrl);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->ProcessRequest();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("List Fleets Request Made"));
}

void UAPITestManager::ListFleets_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("List Fleets Response Received"));

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
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

				return;
			}
		}
		if (JsonObject->HasField(TEXT("errorType")) or JsonObject->HasField(TEXT("errorMessage")))
		{
			FString ErrorType = JsonObject->HasField(TEXT("errorType")) ? JsonObject->GetStringField(TEXT("errorType")) : TEXT("Unknown Error");
			FString ErrorMessage = JsonObject->HasField(TEXT("errorMessage")) ? JsonObject->GetStringField(TEXT("errorMessage")) : TEXT("Unknown Error Message");

			UE_LOG(LogDS, Error, TEXT("Error Type: %s"), *ErrorType);
			UE_LOG(LogDS, Error, TEXT("Error Message: %s"), *ErrorMessage);

			return;
		}
		

		if (JsonObject->HasField(TEXT("$metadata")))
		{
			TSharedPtr<FJsonObject> MetaDataJsonObject = JsonObject->GetObjectField(TEXT("$metadata"));
			FDSMetaData DSMetaData;
			FJsonObjectConverter::JsonObjectToUStruct(MetaDataJsonObject.ToSharedRef(), &DSMetaData);

			DSMetaData.Dump();
		}

		FDSListFleetsResponse ListFleetsResponse;
		if (FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &ListFleetsResponse))
		{
			ListFleetsResponse.Dump();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to convert JSON to ListFleetsResponse"));
		}
	}
}
