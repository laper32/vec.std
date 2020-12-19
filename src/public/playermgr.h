#pragma once

#ifndef _VEC_STD_PLAYERMGR_H_
#define _VEC_STD_PLAYERMGR_H_

#include "extension.h"
#include "sm/ranges.h"
#include "sm/sourcemod_players.h"
#include <string>
#include <sstream>
namespace vec
{
	namespace playermgr
	{
		sp_nativeinfo_t g_PlayerMGRNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);

		namespace API
		{
			static cell_t IsPlayerExist(IPluginContext*, const cell_t*);
			static cell_t GetPlayingCount(IPluginContext*, const cell_t*);
			static cell_t GetAliveCount(IPluginContext*, const cell_t*);
			static cell_t SteamIdConvert(IPluginContext*, const cell_t*);
		}

		inline bool IsPlayerExist(sm::AutoEntity<IGamePlayer*> player, bool alive)
		{
			// not recommend using sm::Ranges here.
			if (!player) return false;
			
			if (player->GetIndex() > sm::GetMaxClients()) return false;

			if (!sm::IsClientConnected(player)) return false;
			if (!sm::IsClientInGame(player) || sm::IsClientInKickQueue(player)) return false;

			if (sm::IsClientSourceTV(player)) return false;
			if (alive && !sm::IsPlayerAlive(player)) return false;
			
			return true;
		}

		inline std::size_t GetPlayingCount()
		{
			std::size_t count = 0;

			for (int i : sm::ranges::Players() | sm::ranges::Connected()) count++;
			return count;
		}

		inline std::size_t GetAliveCount()
		{
			std::size_t count = 0;
			for (int i : sm::ranges::Players() | sm::ranges::Connected() | sm::ranges::Alive()) count++;

			return count;
		}

		//https://gist.github.com/almirsarajcic/4664387
		inline std::string Steam64Convert(uint64_t in, sm::AuthIdType type)
		{
			std::string Ret;
			switch (type)
			{
			case sm::AuthIdType::AuthId_Steam2:
			{

				std::string steam3 = std::to_string(in);
				steam3.erase(steam3.begin(), steam3.begin() + 3);

				steam3 = std::to_string(std::stoull(steam3) - 61197960265728);

				Ret = "STEAM_0:" + std::to_string(in % 2) + ":" + std::to_string(std::stoul(steam3) / 2);
				// Steam_0:y:z
				//z=steam3/2
				//y=steam64%2

				break;
			}
			case sm::AuthIdType::AuthId_Steam3:
			{
				Ret = std::to_string(in);
				Ret.erase(Ret.begin(), Ret.begin() + 3);

				Ret = std::to_string(std::stoull(Ret) - 61197960265728);
				break;
			}
			case sm::AuthIdType::AuthId_SteamID64:
			{
				Ret = std::to_string(in);
				break;
			}
			default: smutils->LogError(myself, "Unsupported authid type. Only accepts steam2, steam3 and steam64."); break;
			}
			return Ret;
		}

		inline std::string Steam3Convert(uint32_t in, sm::AuthIdType type)
		{
			std::string Ret;
			switch (type)
			{

			case sm::AuthIdType::AuthId_Steam2:
			{
				uint64_t steam64 = std::stoull("765" + std::to_string(in + 61197960265728));

				Ret = "STEAM_0:" + std::to_string(steam64 % 2) + ":" + std::to_string(in / 2);
				break;
			}
			case sm::AuthIdType::AuthId_Steam3: {
				Ret = std::to_string(in);
				break;
			}
			case sm::AuthIdType::AuthId_SteamID64:
			{
				Ret = "765" + std::to_string(in + 61197960265728);
				break;
			}
			default: smutils->LogError(myself, "Unsupported authid type. Only accepts steam2, steam3 and steam64."); break;
			}
			return Ret;
		}

		inline std::string Steam32Convert(std::string in, sm::AuthIdType type)
		{
			/*
			ID 64 = 76561197960265728 + (B*2) + A
			ID 32 = STEAM_0:A:B
			*/
			std::string Ret;

			// before processing, we must handle it first.
			std::vector<std::string> template_tokens;
			std::istringstream iss(in);
			std::string temp;
			while (std::getline(iss, temp, ':')) template_tokens.push_back(temp);

			switch (type)
			{
			case sm::AuthIdType::AuthId_Steam2:
			{
				Ret = in;
				break;
			}
			case sm::AuthIdType::AuthId_Steam3:
			{
				// Steam_0:y:z
				//z=steam3/2
				//y=steam64%2

				Ret = std::to_string(std::stoul(template_tokens.at(2)) * 2);
				break;
			}
			case sm::AuthIdType::AuthId_SteamID64:
			{
				Ret = std::to_string(76561197960265728 + std::stoul(template_tokens.at(2)) * 2 + std::stoul(template_tokens.at(1)));
				break;
			}
			default: smutils->LogError(myself, "Unsupported authid type. Only accepts steam2, steam3 and steam64."); break;
			}

			return Ret;
		}

		inline std::string SteamIdConvert(std::string in, sm::AuthIdType type)
		{
			std::string out;
			if (in.size())
			{
				if (in.find("STEAM_0:") != in.npos || in.find("STEAM_1:") != in.npos) out = Steam32Convert(in, type);
				else if (in.size() == 17) out = Steam64Convert(std::stoull(in), type);
				else
				{
					if (in.find_first_not_of("0123456789") != in.npos)
						smutils->LogError(myself, "[playermgr::SteamIdConvert] Found character out of digital. Steam3: %s", in.c_str());
					else
					{
						// we using uint64 here.
						uint64_t checker = std::stoull(in);
						if (checker > UINT32_MAX) smutils->LogError(myself, "[playermgr::SteamIdConvert] Arithmetic overflow. Steam3: %s", in.c_str());
						else
						{
							uint32_t temp = checker;
							std::string steam64checker = std::to_string(std::stoull(std::string("765" + std::to_string(temp + 61197960265728))));
							if (steam64checker.size() == 17) out = Steam3Convert(temp, type);
							else smutils->LogError(myself, "[playermgr::SteamIdConvert] Unexpected error occurs. Steam3: %s", in.c_str());
						}
					}
				}
			}
			return out;
		}
	}
}

#endif // !_VEC_STD_PLAYERMGR_H_
