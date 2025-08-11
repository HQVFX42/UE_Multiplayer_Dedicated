# UE_Multiplayer_Dedicated
UE5 Dedicated Server with AWS and GameLift

---
## GameLift Fleets
> https://docs.aws.amazon.com/gameliftservers/latest/developerguide/integration-engines-setup-unreal.html
1. OpenSSL - 2 binary files
   - Perl - programming language
   - NASM - assembler/disassembler
   - Insatl OpenSSL
2. AWS Server SDK - 2 binary files
3. Unreal Engine Server SDK Plugin

## AWS Lambda

## API Gateway

## Game Sessions

## Player Sessions

## AWS Cognito

[Sign In HTTP Request](./Misc/SignInHTTPRequest.md)

[Preventing Duplicate Emails](./Misc/PreventingDuplicateEmails.md)

## Access Tokens

- **Local Player Subsystem?**
    - Token 관리를 위해 game instance클래스와 같이 게임이 실행되고 있는 한 항시 살아있는 local player를 이용하여 액세스하기 위한 클래스
- Refresh Tokens
    - Authentication flows는 cognito → user pools → app client에서 확인 가능
    - sign in AWS Lambda를 이용하여 refresh token timer 동작(Sign in & response → init token → set refresh token timer → refresh token & response → update tokens → set refresh timer)

[Dependency Injection](./Misc/DependencyInjection.md)

[Dashboard](./Misc/Dashboard.md)
