#include "tools.h"

namespace vec
{
	namespace tools
	{
		sp_nativeinfo_t g_ToolNatives[] = {
			{"ToolsGetTeam", API::GetTeam},
			{nullptr, nullptr}
		};

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			g_pShareSys->AddNatives(myself, g_ToolNatives);
			//sharesys->AddNatives(myself, g_ToolsNative);

			return true;
		}

		namespace API
		{
			static cell_t GetTeam(IPluginContext* pContext, const cell_t* params)
			{
				return vec::tools::GetTeam(sm::ent_cast<CBaseEntity*>(params[1]));
			}
		}
	}
}