#pragma once

#include "extension.h"
#include "sm/sdkhooks.h"

namespace vec
{
	namespace tools
	{
		namespace glowshell
		{
			extern EventListener g_GlowShellTransmit;

			void OnClientDisconnected(int client);

			inline CBaseEntity* CreateGlowshell(CBaseEntity* parent);
		}
	}
}