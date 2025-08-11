# Sign In HTTP Request

# Preface

# 내용

1. 호출 후 reaction을 위한 status message delagate 생성
    
    ```cpp
    	UPROPERTY(BlueprintAssignable)
    	FAPIStatusMessage SignInStatusMessageDelegate;
    ```
    
2. delegate에 binding할 함수 구현
    
    ```cpp
    void USignInPage::UpdateStatusMessage(const FString& Message, bool bShouldResetWidgets)
    {
    	TextBlock_StatusMessage->SetText(FText::FromString(Message));
    	if (bShouldResetWidgets)
    	{
    		Button_SignIn->SetIsEnabled(true);
    	}
    }
    ```
    
3. 해당 ui를 총 관리하는 overlay에서 manager를 통해 binding
    
    `PortalManager->SignStatusMessage.AddDynamic(SignInPage, &USignInpage::UpdateStatusMessage);`
    
4. Manager 클래스에서 해당 함수 구현
    1. 설정한 API endpoint 체크
    2. AWS Lamda에서 호출할 함수 구조체 확인(ex. username, password)
    3. API Gateway에서 해당 함수 method 확인(ex. PUT, GET, POST)
    
    ```cpp
    void UPortalManager::SignIn(const FString& Username, const FString& Password)
    {
    	SignInStatusMessageDelegate.Broadcast(TEXT("Signing in.."), false);
    
    	check(APIData);
    
    	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    	Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::SignIn_Response);
    
    	const FString APIUrl = APIData->GetAPIEndpoint(DedicatedServersTags::PortalAPI::SignIn);
    	Request->SetURL(APIUrl);
    	Request->SetVerb(TEXT("POST"));
    	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    
    	LastUsername = Username;
    	TMap<FString, FString> Params = {
    		{ TEXT("username"), Username },
    		{ TEXT("password"), Password }
    	};
    	FString Content = SerializeJsonObject(Params);
    	Request->SetContentAsString(Content);
    	Request->ProcessRequest();
    }
    ```
    
5. 해당 request를 받아올 response 함수 구현
    
    ```cpp
    void UPortalManager::SignIn_Response(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
    	if (!bWasSuccessful)
    	{
    		SignInStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
    		return;
    	}
    
    	TSharedPtr<FJsonObject> JsonObject;
    	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
    	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
    	{
    		if (ContainsErrors(JsonObject))
    		{
    			SignInStatusMessageDelegate.Broadcast(HTTPStatusMessages::SomethingWentWrong, true);
    			return;
    		}
    
    		FDSInitiateAuthResponse InitiateAuthResponse;
    		FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &InitiateAuthResponse);
    		//InitiateAuthResponse.Dump();
    		//todo: after signing in
    	}
    }
    ```