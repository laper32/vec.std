#pragma once

#ifndef _VEC_STD_FUNCTIONS_H_
#define _VEC_STD_FUNCTIONS_H_

namespace vec
{
	namespace functions
	{
		void OnClientPreAdminCheck(int client);
		void OnClientPostAdminCheck(int client);
		void OnClientPutInServer(int client);
		void OnClientDisconnected(int client);
		//bool OnClientCommand(edict_t* pEntity, const CCommand& args);
		//bool OnClientSay(int id, const CCommand& command, bool team);
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);
	}
}

#endif // !_VEC_STD_FUNCTIONS_H_