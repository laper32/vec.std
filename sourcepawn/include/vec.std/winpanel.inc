#if defined _vec_std_winpanel_included
#endinput
#endif
#define _vec_std_winpanel_included

native void SendWinPanelText(int client, int holdtime, const char[] msg);

native void SendWinPanelTextAll(int holdtime, const char[] msg);