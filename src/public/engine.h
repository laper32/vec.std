#pragma once

#ifndef _VEC_STD_ENGINE_H_
#define _VEC_STD_ENGINE_H_

#include "extension.h"

namespace vec
{
	namespace engine
	{
		extern int Player_Spotted;
		extern int Player_SpottedByMask;
		extern int Player_ProgressBarStartTime;
		extern int Player_ProgressBarDuration;
		extern int Player_BlockingUseActionInProgress;
		extern int Entity_SimulationTime;

		sp_nativeinfo_t g_EngineNative[];

		namespace API
		{
			static cell_t InitSendPropOffset(IPluginContext*, const cell_t*);
		}

		bool SDK_OnLoad(char* error, size_t maxlen, bool late);

		inline void InitSendPropOffset(int &offset, const char* _class, const char* _prop);
	}
}

#endif // !_VEC_STD_ENGINE_H_
