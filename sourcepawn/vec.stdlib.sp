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
    char buffer[256];
    FormatEx(buffer, sizeof(buffer), "<font size=\"7\" color=\"#00ff00\">Font size 7 and Green color</font>\nClient: %N", client);
    SendWinPanelText(client, 5, buffer);
    // CreateWinPanelText(client, 5, "<font size=\"7\" color=\"#00ff00\">Font size 7 and Green color</font>\nClient: %N", client);
    PrintToChatAll("cs_win_panel_round has created.");

}

void NativesOnInit()
{
    CreateNative("SendWinPanelText", API_SendWinPanelText);
    CreateNative("SendWinPanelTextAll", API_SendWinPanelTextAll);
}

public int API_SendWinPanelText(Handle plugin, int numParams)
{
    //inline void CreateWinPanelText(int client, int holdtime, const char[] msg, any ...)
    int client = GetNativeCell(1);
    if (client <= 0 || client > MaxClients) ThrowNativeError(SP_ERROR_NATIVE, "Client index: %d is invalid.", client);

    int holdtime = GetNativeCell(2);
    if (holdtime < 0) ThrowNativeError(SP_ERROR_NATIVE, "Hold time must >=0, but you have input: %d", holdtime);

    if (GetEngineVersion() != Engine_CSGO) ThrowNativeError(SP_ERROR_NATIVE, "This function only supports CSGO.");

    char msg[256];
    GetNativeString(3, msg, sizeof(msg));

    CreateWinPanelText(client, holdtime, msg);
    return 1;
}

public int API_SendWinPanelTextAll(Handle plugin, int numParams)
{
    int holdtime = GetNativeCell(1);
    if (holdtime < 0) ThrowNativeError(SP_ERROR_NATIVE, "Hold time must >=0, but you have input: %d", holdtime);

    if (GetEngineVersion() != Engine_CSGO) ThrowNativeError(SP_ERROR_NATIVE, "This function only supports CSGO.");

    char msg[256];
    GetNativeString(2, msg, sizeof(msg));
    CreateWinPanelTextAll(holdtime, msg);
    return 1;
}