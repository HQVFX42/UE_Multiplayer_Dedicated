#include "GameplayTags/DedicatedServersTags.h"

namespace DedicatedServersTags
{
	namespace GameSessionsAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ListFleets,
			"DedicatedServersTags.GameSeesionAPI.ListFleets",
			"List fleets resource on the Game Sessions API.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(FindOrCreateGameSession,
			"DedicatedServersTags.GameSeesionAPI.FindOrCreateGameSession",
			"Retrieves an ACTIVE game session, creating one if one does not exist on the Game Sessions API.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(CreatePlayerSession,
			"DedicatedServersTags.GameSeesionAPI.CreatePlayerSession",
			"Creates a new player Session on the Game Sessions API.");
	}
	namespace PortalAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignUp,
			"DedicatedServersTags.PortalAPI.SignUp",
			"Creates a new user in the Portal API.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ConfirmSignUp,
			"DedicatedServersTags.PortalAPI.ConfirmSignUp",
			"Confirms a new user in Portal API.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignIn,
			"DedicatedServersTags.PortalAPI.SignIn",
			"Retrieves Access Token, Id Token and Refresh Token in Portal API.");
	}
}