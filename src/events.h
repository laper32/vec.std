#pragma once

class IGameEventManager2;

namespace vec::events
{
	void Event_OnRoundStart(IGameEvent* pEvent);
	void Event_OnRoundEnd(IGameEvent* pEvent);
	void Event_OnWinPanelRound(IGameEvent* pEvent);
	void Event_OnPlayerSpawn(IGameEvent* pEvent);
	void Event_OnPlayerDeath(IGameEvent* pEvent);
	void Event_OnPlayerTeam(IGameEvent* pEvent);
	extern IGameEventManager2* gameevents;
	bool SDK_OnLoad(char* error, size_t maxlength, bool late);
	bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late);
	void SDK_OnUnload();
}