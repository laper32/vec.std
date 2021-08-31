#pragma once
#include <list>
#include <memory>
namespace vec::command
{
    // For export, aka, CBaseEntity, edict_t, etc, rather than SayHook internel!
    // Do not mix them up!
    void SetCommandClient(int client);
    int GetCommandClient();
    class ConCommandInfo
    {
    public:
        explicit ConCommandInfo(const char* m_pName, bool m_bChatTrigger) : m_pName(m_pName), m_bChatTrigger(m_bChatTrigger) {}
        ~ConCommandInfo() {}
        // Get the console command name, used for invoke
        const char* GetName() { return this->m_pName; }
        // Does this command will be triggered by chat?
        bool        IsChatTrigger() { return this->m_bChatTrigger; }
    private:
        const char* m_pName;
        bool        m_bChatTrigger;
    };
	extern std::list<std::unique_ptr<ConCommandInfo>> g_CommandInfoList;
	bool SDK_OnLoad(char* error, size_t maxlength, bool late);
	bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late);
	void SDK_OnUnload();
}