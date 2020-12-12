#include "extension.h"

#include <ISmmPlugin.h>
#include <igameevents.h>

#include "events.h"

namespace vec
{
	namespace events
	{
		IGameEventManager2* gameevents = nullptr;

		class EventManager : public IGameEventListener2
		{
		public:
			void FireGameEvent(IGameEvent* pEvent) override
			{
				if (pEvent && !strcmp(pEvent->GetName(), "round_start"))
				{
					Event_OnRoundStart(pEvent);
				}

				if (pEvent && !strcmp(pEvent->GetName(), "round_end"))
				{
					Event_OnRoundEnd(pEvent);
				}

				if (pEvent && !strcmp(pEvent->GetName(), "cs_win_panel_round"))
				{
					Event_OnWinPanelRound(pEvent);
				}

				if (pEvent && !strcmp(pEvent->GetName(), "player_spawn"))
				{
					Event_OnPlayerSpawn(pEvent);
				}

				if (pEvent && !strcmp(pEvent->GetName(), "player_death"))
				{
					Event_OnPlayerDeath(pEvent);
				}

				if (pEvent && !strcmp(pEvent->GetName(), "player_team"))
				{
					Event_OnPlayerTeam(pEvent);
				}
			}

			int GetEventDebugID() override
			{
				return EVENT_DEBUG_ID_INIT;
			}
		} g_EventManager;
		void Event_OnRoundStart(IGameEvent* pEvent)
		{

		}
		void Event_OnRoundEnd(IGameEvent* pEvent)
		{

		}
		void Event_OnWinPanelRound(IGameEvent* pEvent)
		{

		}
		void Event_OnPlayerSpawn(IGameEvent* pEvent)
		{

		}
		void Event_OnPlayerDeath(IGameEvent* pEvent)
		{

		}
		void Event_OnPlayerTeam(IGameEvent* pEvent)
		{

		}
		
		bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
		{
			GET_V_IFACE_CURRENT(GetEngineFactory, gameevents, IGameEventManager2, INTERFACEVERSION_GAMEEVENTSMANAGER2);

			return true;
		}

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			gameevents->AddListener(&g_EventManager, "round_start", true);
			gameevents->AddListener(&g_EventManager, "player_spawn", true);
			gameevents->AddListener(&g_EventManager, "player_death", true);

			return true;
		}

		void SDK_OnUnload() 
		{
			gameevents->RemoveListener(&g_EventManager);
		}
	}
}