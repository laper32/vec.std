#pragma semicolon 1
#pragma newdecls required
#include <vec.std>
#include "vec.stdlib/winpanel.sp"

public Plugin myinfo =
{
    name        = "Vector community - Standard library",
    author      = "laper32",
    description = "Standard library",
    version     = "1.0.0.0",
    url         = "vec"
}


public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
    NativesOnInit();
    return APLRes_Success;
}

public void OnPluginStart()
{
    RegConsoleCmd("sm_try_win_panel", cmd_TryWinPanel);

    // HookEvent("cs_win_panel_round", HookOfWinpanelRound);
}

public void OnMapEnd()
{
    WinPanelOnUnLoad();
}

public void OnClientDisconnect(int client)
{
    WinPanelOnClientDisconnect(client);
}

public Action cmd_TryWinPanel(int client, int params)
{
    ConstructWinPanel(client, 5, "<font size=\"7\" color=\"#00ff00\">Font size 7 and Green color</font>");
    PrintToChatAll("cs_win_panel_round has created.");

}

void NativesOnInit()
{

}