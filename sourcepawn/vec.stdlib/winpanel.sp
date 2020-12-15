/*
	https://forums.alliedmods.net/showthread.php?t=326935

	"cs_win_panel_round"
	{
		"show_timer_defend"	"bool"
		"show_timer_attack"	"bool"
		"timer_time"		"short"
		
		"final_event"		"byte"		//define in cs_gamerules.h
		
		"funfact_token"		"string"
		"funfact_player"	"short"
		"funfact_data1"		"long"
		"funfact_data2"		"long"
		"funfact_data3"		"long"
	}
*/

// 晚一点转移到C++
// 现在stdlib里凑合用
Handle msgHandle[MAXPLAYERS+1] = null;

methodmap WinPanel < Event
{
    property bool show_timer_defend
    {
        // by default is true
        public get() { return this.GetBool("show_timer_defend", true); }
        public set(bool show) { this.SetBool("show_timer_defend", show); }
    }

    property bool show_timer_attack
    {
        // by default is true
        public get() { return this.GetBool("show_timer_attack", true); }
        public set(bool show) { this.SetBool("show_timer_attack", show); }
    }

    // this is short, remember.
    property int timer_time
    {
        public get() { return this.GetInt("timer_time", 0); }
        public set(int val) { this.SetInt("timer_time", val); }
    }

    property int final_event
    {
        public get() { return this.GetInt("final_event", 0); }
        public set(int val) { this.SetInt("final_event", val); }
    }

    property int funfact_player
    {
        public get() { return this.GetInt("funfact_player", 0); }
        public set(int val) { this.SetInt("funfact_player", val); }
    }

    property int funfact_data1
    {
        public get() { return this.GetInt("funfact_data1", 0); }
        public set(int val) { this.SetInt("funfact_data1", val); }
    }

    property int funfact_data2
    {
        public get() { return this.GetInt("funfact_data2", 0); }
        public set(int val) { this.SetInt("funfact_data2", val); }
    }

    property int funfact_data3
    {
        public get() { return this.GetInt("funfact_data3", 0); }
        public set(int val) { this.SetInt("funfact_data3", val); }
    }

    public WinPanel()
    {
        Event event = CreateEvent("cs_win_panel_round", true);

        if(!event) ThrowNativeError(SP_ERROR_NATIVE, "Unable to create event \"cs_win_panel_round\": The event is nullptr.");

        return view_as<WinPanel>(event);
    }

    public void Init()
    {
        this.show_timer_attack = false;
        this.show_timer_defend = false;
        this.final_event = 0;
        this.SetString("funfact_token", "");
        this.funfact_player = 0;
        this.funfact_data1 = 0;
        this.funfact_data2 = 0;
        this.funfact_data3 = 0;
    }
    
    public void Destroy() { 
        delete view_as<Event>(this); 
        }

    public void Display(int client, const char[] msg, any ...)
    {
        char buffer[256];
        VFormat(buffer, sizeof(buffer), msg, 3);
        this.funfact_player = GetClientUserId(client);
        this.SetString("funfact_token", buffer);
        this.FireToClient(client);
        this.funfact_player = 0;
    }

    public void DisplayAll(const char[] msg, any ...)
    {
        char buffer[256];
        VFormat(buffer, sizeof(buffer), msg, 2);
        for (int i = 1; i < MaxClients; i++)
        {
            if (IsPlayerExist(i, false) && !IsFakeClient(i)) 
                this.Display(i, buffer);
        }
    }
}

inline void CreateWinPanelText(int client, int holdtime, const char[] msg, any ...)
{
    char buffer[256];
    VFormat(buffer, sizeof(buffer), msg, 4);

    WinPanel panel = new WinPanel();
    panel.Init();
    panel.timer_time = holdtime;
    panel.Display(client, buffer);
    panel.Destroy();
    
    delete msgHandle[client];
    msgHandle[client] = CreateTimer(float(panel.timer_time), EraseExistingMessage, GetClientUserId(client), TIMER_FLAG_NO_MAPCHANGE);
}

inline void CreateWinPanelTextAll(int holdtime, const char[] msg, any ...)
{
    char buffer[256];
    VFormat(buffer, sizeof(buffer), msg, 3);

    WinPanel panel = new WinPanel();
    panel.Init();
    panel.timer_time = holdtime;
    panel.DisplayAll(msg);
    panel.Destroy();

    for (int i = 0; i < MaxClients; i++)
    {
        if (IsPlayerExist(i, false))
        {
            delete msgHandle[i];
            msgHandle[i] = CreateTimer(float(panel.timer_time), EraseExistingMessage, GetClientUserId(i), TIMER_FLAG_NO_MAPCHANGE);
        }
    }
}

void WinPanelOnUnLoad()
{
    for (int i = 1; i <= MaxClients; i++)
    {
        msgHandle[i] = null;
    }
}

void WinPanelOnClientDisconnect(int client)
{
    delete msgHandle[client];
}

public Action EraseExistingMessage(Handle timer, int userid)
{
    int client = GetClientOfUserId(userid);

    if (client)
    {
        WinPanel panel = new WinPanel();
        panel.Init();
        panel.Display(client, "");
        panel.Destroy();
    }

    msgHandle[client] = null;
    return Plugin_Stop;
}