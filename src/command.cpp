#include "extension.h"
#include "command.h"
#include <list>
namespace vec::command {
    
    std::list<std::unique_ptr<ConCommandInfo>> g_CommandInfoList;

    // ExecuteStringCommand detour begin
    
    CDetour* DExecuteStringCommand = nullptr;

    void strtrim(char* str)
    {
        int start = 0; // number of leading spaces
        char* buffer = str;
        while (*str && *str++ == ' ') ++start;
        while (*str++); // move to end of string
        int end = str - buffer - 1;
        while (end > 0 && buffer[end - 1] == ' ') --end; // backup over trailing spaces
        buffer[end] = 0; // remove trailing spaces
        if (end <= start || start == 0) return; // exit if no leading spaces or string is now empty
        str = buffer + start;
        while ((*buffer++ = *str++));  // remove leading spaces: K&R
    }
    DETOUR_DECL_MEMBER1(OnExecuteStringCommand, bool, const char*, sMsg)
    {
        if (sMsg)
        {
            // internal command has only 512 alloc...
            char command[512];
            V_strncpy(command, sMsg, sizeof(command));
            if (strlen(command) > 0) strtrim(command);
            // this can block sm xxxx (for example: sm plugins)
            // and also meta xxx (for example: meta list)
            if (!V_strncasecmp(command, "sm ", 3) || !V_strncasecmp(command, "meta ", 5))
            {
                #ifdef WIN32
                int client = ((IClient*)(this))->GetPlayerSlot() + 1;
                #else
                int client = ((IClient*)((intptr_t)this + sizeof(void*)))->GetPlayerSlot() + 1;
                #endif
                // client > 0 => not console, and does a real player
                if (client)
                {
                    // no way to get plugins
                    return false;
                }
            }
        }
        return DETOUR_MEMBER_CALL(OnExecuteStringCommand)(sMsg);
    }

    bool CreateExecuteStringCommandDetour()
    {
        CDetourManager::Init(smutils->GetScriptingEngine(), g_pGameConf);

        DExecuteStringCommand = DETOUR_CREATE_MEMBER(OnExecuteStringCommand, "ExecuteStringCommand");
        if (!DExecuteStringCommand)
        {
            smutils->LogError(myself, "Failed to create \"ExecuteStringCommand\" detour.");
            return false;
        }
        DExecuteStringCommand->EnableDetour();
        return true;
    }

    void RemoveExecuteStringCommandDetour()
    {
        if (DExecuteStringCommand) DExecuteStringCommand->Destroy();
    }

    // ExecuteStringCommand detour end

    SH_DECL_HOOK1_void(ConCommand, Dispatch, SH_NOATTRIB, false, const CCommand&);
    SH_DECL_HOOK1_void(IServerGameClients, SetCommandClient, SH_NOATTRIB, false, int);
    
    

    std::vector<std::string> split(const std::string& s, const std::string& c)
    {
        std::vector<std::string> ret;
        std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;

        while (std::string::npos != pos2)
        {
            ret.push_back(s.substr(pos1, pos2 - pos1));
            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if (pos1 != s.length()) ret.push_back(s.substr(pos1));

        return ret;
    }

    bool OnClientSayPre(int client, const CCommand& command)
    {
        // client == 0 => server side uses say command.
        // we don't want server side handle anything.
        // Just terminate it.
        if (!client) return false;

        std::string message = command.Arg(1);


        if (!message.empty())
        {
            // In sourcemod, if the command caller is started with '/' -> it will execute the command,
            // and not show what command is invoked at the chat board.
            if (message[0] == '/' || (message[0] == '\"' && message[1] == '/'))
            {
                if (message.front() == '\"' && message.back() == '\"')
                    message = message.substr(1, message.size() - 2);

                std::vector<std::string> cmd = split(message, " ");

                // the 0 => /command
                std::string tempStr = cmd[0].erase(0, 1); // remove '/'
                std::string commandStr = "";
                if (!strncasecmp("sm_", tempStr.c_str(), 3))
                {
                    commandStr = tempStr;
                }
                else
                {
                    commandStr = "sm_" + tempStr;
                }

                ConCommand* pCommand = icvar->FindCommand(commandStr.c_str());
                if (pCommand)
                {
                    for (auto& i : g_CommandInfoList)
                    {
                        if (!strcmp(i->GetName(), pCommand->GetName()))
                        {
                            if (!i->IsChatTrigger())
                            {
                                return false;
                            }
                            CCommand command;
                            command.Tokenize(message.erase(0, 1).c_str());
                            pCommand->Dispatch(command);
                            return true;
                        }
                    }
                }
                return false;
            }
        }

        return false;
    }

    bool OnClientSayPost(int client, const CCommand& command)
    {
        // client = 0 => sent from console
        // console: say xxx
        // should not handle anything
        if (!client) return false;

        std::string message = command.Arg(1);

        if (!message.empty())
        {
            // If start with '!' -> normally display (idk why the rule is differ from the '/'...)
            if (message[0] == '!' || (message[0] == '\"' && message[1] == '!'))
            {
                if (message.front() == '\"' && message.back() == '\"')
                    message = message.substr(1, message.size() - 2);

                std::vector<std::string> cmd = split(message, " ");

                // the 0 => /command
                std::string tempStr = cmd[0].erase(0, 1); // remove '/'
                std::string commandStr = "";
                if (!strncasecmp("sm_", tempStr.c_str(), 3))
                {
                    commandStr = tempStr;
                }
                else
                {
                    commandStr = "sm_" + tempStr;
                }

                ConCommand* pCommand = icvar->FindCommand(commandStr.c_str());
                if (pCommand)
                {
                    for (auto& i : g_CommandInfoList)
                    {
                        if (!strcmp(i->GetName(), pCommand->GetName()))
                        {
                            if (!i->IsChatTrigger())
                            {
                                return false;
                            }
                            CCommand command;
                            command.Tokenize(message.erase(0, 1).c_str());
                            pCommand->Dispatch(command);
                            return false;
                        }
                    }
                }
                return false;
            }
        }

        return false;
    }
    class CommandHook
    {
    public:
        void DispatchSayPre(const CCommand& command)
        {
            bool handled = false;
            handled |= OnClientSayPre(last_command_client_, command);
            if (handled)
                RETURN_META(MRES_SUPERCEDE);
            RETURN_META(MRES_IGNORED);
        }
        void DispatchSayPost(const CCommand& command)
        {
            bool handled = false;
            handled |= OnClientSayPost(last_command_client_, command);
            if (handled)
                RETURN_META(MRES_SUPERCEDE);
            RETURN_META(MRES_IGNORED);
        }
        void DispatchSayTeamPre(const CCommand& command)
        {
            bool handled = false;

            if (handled)
                RETURN_META(MRES_SUPERCEDE);
            RETURN_META(MRES_IGNORED);
        }
        void DispatchSayTeamPost(const CCommand& command)
        {
            bool handled = false;

            if (handled)
                RETURN_META(MRES_SUPERCEDE);
            RETURN_META(MRES_IGNORED);
        }
        void SetCommandClient(int client)
        {
            last_command_client_ = client + 1;
        }
        int last_command_client_ = 0;
    } g_CommandHook;
    static int g_hookIndexDispatchSayPre;
    static int g_hookIndexDispatchSayPost;
    static int g_hookIndexDispatchSayTeamPre;
    static int g_hookIndexDispatchSayTeamPost;
    static int g_hookIndexSetCommandClient;

    // For export, aka, CBaseEntity, edict_t, etc, rather than SayHook internel!
    // Do not mix them up!
    void SetCommandClient(int client)
    {
        g_CommandHook.last_command_client_ = client;
    }

    int GetCommandClient()
    {
        return g_CommandHook.last_command_client_;
    }

    class BaseAccessor : public IConCommandBaseAccessor
    {
    public:
        bool RegisterConCommandBase(ConCommandBase* pCommandBase)
        {
            /* Always call META_REGCVAR instead of going through the engine. */
            return META_REGCVAR(pCommandBase);
        }
    } s_BaseAccessor;
    
    // Simple integration of Console command registration
    void RegConsoleCmd(const char* pName, FnCommandCallbackV1_t callback, const char* pHelpString = 0, 
        int flags = 0, FnCommandCompletionCallback completionFunc = 0, bool chatTrigger = true)
    {
        if (icvar->FindCommand(pName) != nullptr)
        {
            smutils->LogError(myself, "The command has been registered: \"%s\"", pName);
            return;
        }
        new ConCommand(pName, callback, pHelpString, flags, completionFunc);

        g_CommandInfoList.push_back(std::make_unique<ConCommandInfo>(pName, chatTrigger));
    }
    void RegConsoleCmd(const char* pName, FnCommandCallback_t callback, const char* pHelpString = 0, 
        int flags = 0, FnCommandCompletionCallback completionFunc = 0, bool chatTrigger = true)
    {
        if (icvar->FindCommand(pName) != nullptr)
        {
            smutils->LogError(myself, "The command has been registered: \"%s\"", pName);
            return;
        }
        new ConCommand(pName, callback, pHelpString, flags, completionFunc);
        
        g_CommandInfoList.push_back(std::make_unique<ConCommandInfo>(pName, chatTrigger));
    }
    void RegConsoleCmd(const char* pName, ICommandCallback* pCallback, const char* pHelpString = 0, 
        int flags = 0, ICommandCompletionCallback* pCommandCompletionCallback = 0, bool chatTrigger = true)
    {
        if (icvar->FindCommand(pName) != nullptr)
        {
            smutils->LogError(myself, "The command has been registered: \"%s\"", pName);
            return;
        }
        new ConCommand(pName, pCallback, pHelpString, flags, pCommandCompletionCallback);

        g_CommandInfoList.push_back(std::make_unique<ConCommandInfo>(pName, chatTrigger));
    }

    static void CommandCallback_TestSayHook(const CCommand& command)
    {
        int client = GetCommandClient();

        //std::string message = "Command triggered -> client index: " + std::to_string(client);
        char buffer[256];
        smutils->Format(buffer, sizeof(buffer), "Command triggered: client index: %d\n", client);
        if (!client)
        {
            META_CONPRINTF(buffer);
            return;
        }

        if (client)
        {
            sm::PrintToChatAll("Seeing this means it success");
        }
        for (int i = 1; i < command.ArgC(); i++)
        {
            sm::PrintToChatAll(command.Arg(i));
        }
        sm::PrintToChatAll(buffer);

        return;
    }


    static void InitCMD()
    {
        
        RegConsoleCmd("sm_test_sayhook", CommandCallback_TestSayHook, "Test sayhook");
        
    }

    bool SDK_OnLoad(char* error, size_t maxlength, bool late)
    {
        ConCommand* say = icvar->FindCommand("say");
        ConCommand* say_team = icvar->FindCommand("say_team");

        InitCMD();

        g_hookIndexDispatchSayPre = SH_ADD_HOOK(ConCommand, Dispatch, say, SH_MEMBER(&g_CommandHook, &CommandHook::DispatchSayPre), false);
        g_hookIndexDispatchSayPost = SH_ADD_HOOK(ConCommand, Dispatch, say, SH_MEMBER(&g_CommandHook, &CommandHook::DispatchSayPost), true);
        g_hookIndexDispatchSayTeamPre = SH_ADD_HOOK(ConCommand, Dispatch, say_team, SH_MEMBER(&g_CommandHook, &CommandHook::DispatchSayTeamPre), false);
        g_hookIndexDispatchSayTeamPost = SH_ADD_HOOK(ConCommand, Dispatch, say_team, SH_MEMBER(&g_CommandHook, &CommandHook::DispatchSayTeamPre), true);
        g_hookIndexSetCommandClient = SH_ADD_HOOK(IServerGameClients, SetCommandClient, serverClients, SH_MEMBER(&g_CommandHook, &CommandHook::SetCommandClient), false);
        
        CreateExecuteStringCommandDetour();

        return true;
    }
    bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
    {
        g_pCVar = icvar;
        ConVar_Register(0, &s_BaseAccessor);
        return true;
    }
    void SDK_OnUnload()
    {
        SH_REMOVE_HOOK_ID(g_hookIndexDispatchSayPre);
        SH_REMOVE_HOOK_ID(g_hookIndexDispatchSayPost);
        SH_REMOVE_HOOK_ID(g_hookIndexDispatchSayTeamPre);
        SH_REMOVE_HOOK_ID(g_hookIndexDispatchSayTeamPost);
        SH_REMOVE_HOOK_ID(g_hookIndexSetCommandClient);

        RemoveExecuteStringCommandDetour();
    }
}