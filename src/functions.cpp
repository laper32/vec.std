#include "functions.h"

#include "public/tools.h"
#include "public/engine.h"
#include "public/utils.h"
#include "public/playermgr.h"
#include "public/hashlib.h"
namespace vec
{
	namespace functions
	{
		void OnClientPreAdminCheck(int client)
		{

		}
		void OnClientPostAdminCheck(int client)
		{

		}
		void OnClientPutInServer(int client)
		{

		}
		void OnClientDisconnected(int client)
		{
		}
		//bool OnClientCommand(edict_t* pEntity, const CCommand& args);
		//bool OnClientSay(int id, const CCommand& command, bool team);

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			vec::engine::SDK_OnLoad(error, maxlen, late);
			vec::tools::SDK_OnLoad(error, maxlen, late);
			vec::utils::SDK_OnLoad(error, maxlen, late);
			vec::playermgr::SDK_OnLoad(error, maxlen, late);
			vec::hashlib::SDK_OnLoad(error, maxlen, late);
			return true;
		}
	}
}