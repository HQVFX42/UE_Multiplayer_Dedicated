# Dependency Injection

local player subsystem에서 portalmanager를 액세스하고

portalmanager에서도 local player subsystem을 액세스한다

이를 `interface`를 사용하여 클래스 구조를 개선시킬 수 있다

즉, localplayersubsystem이 portalmanager를 직접가지고 있는 것보다는 interface를 이용해서 circular dependency를 제거할 수 있다

- PortalManager는 interface 상속

```cpp
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPortalManagement : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEDICATEDSERVERS_API IPortalManagement
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void RefreshTokens(const FString& RefreshToken) = 0;
};

```

```cpp
UCLASS()
class DEDICATEDSERVERS_API UPortalManager : public UHTTPRequestManager, public IPortalManagement
{
	GENERATED_BODY()	
	
public:	
	// IPortalManagement interface
	virtual void RefreshTokens(const FString& RefreshToken) override;
}

```

- LocalPlayerSubsystem은 interface 호출

```cpp
class IPortalManagement;

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERS_API UDSLocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	void InitializeTokens(const FDSAuthenticationResult& AuthResult, TScriptInterface<IPortalManagement> PortalManagement);
	void SetRefreshTokenTimer();
	void UpdateTokens(const FString& AccessToken, const FString& IdToken);

private:
	UPROPERTY()
	FDSAuthenticationResult AuthenticationResult;
	
	//UPROPERTY()
	//TObjectPtr<UPortalManager> PortalManager;

	UPROPERTY()
	TScriptInterface<IPortalManagement> PortalManagementInterface;
};
```

```cpp

void UDSLocalPlayerSubsystem::InitializeTokens(const FDSAuthenticationResult& AuthResult, TScriptInterface<IPortalManagement> PortalManagement)
{
	AuthenticationResult = AuthResult;
	PortalManagementInterface = PortalManagement;
	SetRefreshTokenTimer();
}

void UDSLocalPlayerSubsystem::SetRefreshTokenTimer()
{
	UWorld* World = GetWorld();
	if (IsValid(World) and IsValid(PortalManagementInterface.GetObject()))
	{
		FTimerDelegate RefreshDelegate;
		RefreshDelegate.BindLambda([this]()
			{
				PortalManagementInterface->RefreshTokens(AuthenticationResult.RefreshToken);
			});
		World->GetTimerManager().SetTimer(RefreshTimer, RefreshDelegate, TokenRefreshInterval, false);
	}
}

void UDSLocalPlayerSubsystem::UpdateTokens(const FString& AccessToken, const FString& IdToken)
{
	AuthenticationResult.AccessToken = AccessToken;
	AuthenticationResult.IdToken = IdToken;
	AuthenticationResult.Dump();
	SetRefreshTokenTimer();
}
```