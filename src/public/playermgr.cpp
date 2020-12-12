#include "playermgr.h"

namespace vec
{
	namespace playermgr
	{
		sp_nativeinfo_t g_PlayerMGRNatives[] = {
			{"IsPlayerExist",	API::IsPlayerExist},
			{"GetPlayingCount",	API::GetPlayingCount},
			{"GetAliveCount",	API::GetAliveCount},
			{nullptr,			nullptr}
		};
		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_PlayerMGRNatives);
			return true;
		}

		namespace API
		{
			static cell_t IsPlayerExist(IPluginContext* pContext, const cell_t* params)
			{
				return vec::playermgr::IsPlayerExist(params[1], params[2]);
			}
			static cell_t GetPlayingCount(IPluginContext* pContext, const cell_t* params)
			{
				return vec::playermgr::GetPlayingCount();
			}
			static cell_t GetAliveCount(IPluginContext* pContext, const cell_t* params)
			{
				return vec::playermgr::GetAliveCount();
			}
		}
	}
}