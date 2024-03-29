#include "client.h"
#include "command.h"
namespace vec::client
{
	bool OnClientCommand(edict_t* pEntity, const CCommand& args)
	{
		if (pEntity)
		{
			ConCommand* pCommand = icvar->FindCommand(args.Arg(0));
			if (pCommand)
			{
				for (auto& i : command::g_CommandInfoList)
				{
					if (!strcmp(i->GetName(), pCommand->GetName()))
					{
						pCommand->Dispatch(args);
						return true;
					}
				}
			}
		}
		return false;
	}

	bool OnClientCommand_Post(edict_t* pEntity, const CCommand& args)
	{
		return false;
	}

	class ServerGameClientsHooks
	{
	public:
		// IServerGameClients hooks
		bool OnClientConnect(edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen) { RETURN_META_VALUE(MRES_IGNORED, true); }
		bool OnClientConnect_Post(edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen) { RETURN_META_VALUE(MRES_IGNORED, true); }
		void OnClientPutInServer(edict_t* pEntity, char const* playername) { RETURN_META(MRES_IGNORED); }
		void OnClientDisconnect(edict_t* pEntity) { RETURN_META(MRES_IGNORED); }
		void OnClientDisconnect_Post(edict_t* pEntity) { RETURN_META(MRES_IGNORED); }
		void OnClientCommand(edict_t* pEntity, const CCommand& args) {
			bool handled = false;
			command::SetCommandClient(sm::ent_cast<int>(pEntity));
			handled |= client::OnClientCommand(pEntity, args);

			if (handled)
				RETURN_META(MRES_SUPERCEDE);
			RETURN_META(MRES_IGNORED);
		}
		void OnClientCommand_Post(edict_t* pEntity, const CCommand& args) { 
			RETURN_META(MRES_IGNORED); 
		}
		void OnClientCommandKeyValues(edict_t* pEntity, KeyValues* pCommand) { RETURN_META(MRES_IGNORED); }
		void OnClientCommandKeyValues_Post(edict_t* pEntity, KeyValues* pCommand) { RETURN_META(MRES_IGNORED); }
		void OnClientSettingsChanged(edict_t* pEntity) { RETURN_META(MRES_IGNORED); }
	} g_ServerGameClientsHooks;

	class ClientListener : public IClientListener
	{
	public:
		bool OnClientPreAdminCheck(int id) override
		{
			//gameplay::OnClientPreAdminCheck(id);
			return true;
		}
		void OnClientPostAdminCheck(int id) override
		{
			//gameplay::OnClientPostAdminCheck(id);
		}
		void OnClientPutInServer(int id) override
		{
			//gameplay::OnClientPutInServer(id);
		}
		// treat it as OnClientDisconnect_Post
		void OnClientDisconnected(int id) override
		{
			//gameplay::OnClientDisconnected(id);
		}
	} g_ClientListener;

	SH_DECL_HOOK5(IServerGameClients, ClientConnect, SH_NOATTRIB, 0, bool, edict_t*, const char*, const char*, char*, int);
	SH_DECL_HOOK2_void(IServerGameClients, ClientPutInServer, SH_NOATTRIB, 0, edict_t*, const char*);
	SH_DECL_HOOK1_void(IServerGameClients, ClientDisconnect, SH_NOATTRIB, 0, edict_t*);
	SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t*, const CCommand&);
	SH_DECL_HOOK1_void(IServerGameClients, ClientSettingsChanged, SH_NOATTRIB, 0, edict_t*);
	SH_DECL_HOOK2_void(IServerGameClients, ClientCommandKeyValues, SH_NOATTRIB, 0, edict_t*, KeyValues*);


	bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
	{

		return true;
	}

	bool SDK_OnLoad(char* error, size_t maxlen, bool late)
	{
		SH_ADD_HOOK(IServerGameClients, ClientConnect, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientConnect), false);
		SH_ADD_HOOK(IServerGameClients, ClientConnect, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientConnect_Post), true);
		SH_ADD_HOOK(IServerGameClients, ClientPutInServer, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientPutInServer), true);
		SH_ADD_HOOK(IServerGameClients, ClientDisconnect, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientDisconnect), false);
		SH_ADD_HOOK(IServerGameClients, ClientDisconnect, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientDisconnect_Post), true);
		SH_ADD_HOOK(IServerGameClients, ClientCommand, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientCommand), false);
		SH_ADD_HOOK(IServerGameClients, ClientCommand, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientCommand_Post), true);
		SH_ADD_HOOK(IServerGameClients, ClientCommandKeyValues, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientCommandKeyValues), false);
		SH_ADD_HOOK(IServerGameClients, ClientCommandKeyValues, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientCommandKeyValues_Post), true);
		SH_ADD_HOOK(IServerGameClients, ClientSettingsChanged, serverClients, SH_MEMBER(&g_ServerGameClientsHooks, &ServerGameClientsHooks::OnClientSettingsChanged), true);

		playerhelpers->AddClientListener(&g_ClientListener);
		return true;
	}

	void SDK_OnUnload() {

	}
}