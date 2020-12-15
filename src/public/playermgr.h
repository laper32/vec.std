#pragma once

#ifndef _VEC_STD_PLAYERMGR_H_
#define _VEC_STD_PLAYERMGR_H_

#include "extension.h"
#include "sm/ranges.h"
#include "sm/sourcemod_players.h"

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
	}
}

#endif // !_VEC_STD_PLAYERMGR_H_
