#include "engine.h"
#include <stdexcept>

namespace vec
{
	namespace engine
	{
		IGameConfig* g_pGameConf = nullptr;

		int Player_Spotted = -1;
		int Player_SpottedByMask = -1;
		int Player_ProgressBarStartTime = -1;
		int Player_ProgressBarDuration = -1;
		int Player_BlockingUseActionInProgress = -1;
		int Entity_SimulationTime = -1;

		void InitSendPropOffset(int& offset, const char* _class, const char* _prop)
		{
			sm_sendprop_info_t info = {};
			if (!gamehelpers->FindSendPropInfo(_class, _prop, &info))
				throw std::runtime_error("Unable to find: " + (std::string() + _class + _prop));
			offset = info.actual_offset;

			if (offset < -1) throw std::runtime_error("Unable to find send prop: " + (std::string() + _prop));
		}

		
		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			InitSendPropOffset(Player_Spotted, "CBasePlayer", "m_bSpotted");
			InitSendPropOffset(Player_SpottedByMask, "CBasePlayer", "m_bSpottedByMask");
			InitSendPropOffset(Player_ProgressBarStartTime, "CCSPlayer", "m_flProgressBarStartTime");
			InitSendPropOffset(Player_ProgressBarDuration, "CCSPlayer", "m_iProgressBarDuration");
			InitSendPropOffset(Player_BlockingUseActionInProgress, "CCSPlayer", "m_iBlockingUseActionInProgress");
			InitSendPropOffset(Entity_SimulationTime, "CBaseEntity", "m_flSimulationTime");

			return true;
		}

		namespace API
		{
			static cell_t InitSendPropOffset(IPluginContext* pContext, const cell_t* params)
			{
				cell_t* offset;
				char* _class; char* _prop;
				pContext->LocalToPhysAddr(params[1], &offset);
				pContext->LocalToString(params[2], &_class); pContext->LocalToString(params[3], &_prop);
				vec::engine::InitSendPropOffset(*offset, _class, _prop);
				return 0;
			}
		}
	}
}