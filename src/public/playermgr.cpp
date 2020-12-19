#include "playermgr.h"

namespace vec
{
	namespace playermgr
	{
		sp_nativeinfo_t g_PlayerMGRNatives[] = {
			{"IsPlayerExist",	API::IsPlayerExist},
			{"GetPlayingCount",	API::GetPlayingCount},
			{"GetAliveCount",	API::GetAliveCount},
			{"SteamIdConvert",	API::SteamIdConvert},
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
			// native void SteamIdConvert(const char[] input, AuthIdType type, const char[] output, int maxlen)
			static cell_t SteamIdConvert(IPluginContext* pContext, const cell_t* params)
			{
				std::string in;
				sm::interop::cell2native(pContext, params[1], in);
				std::string out;
				sm::AuthIdType type = static_cast<sm::AuthIdType>(params[2]);
				
				if (!in.size())
				{
					pContext->ReportError("The input is empty.");
					return false;
				}

				out = vec::playermgr::SteamIdConvert(in, type);

				if (!out.size())
				{
					pContext->ReportError("Unexpected: the output is empty. Input: %s", in.c_str());
					return false;
				}

				return pContext->StringToLocalUTF8(params[3], params[4], out.c_str(), nullptr);
			}
		}
	}
}