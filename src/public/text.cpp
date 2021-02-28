#include "text.h"

namespace vec
{
	namespace text
	{
		sp_nativeinfo_t g_TextNatives[] = {
			{nullptr, nullptr}
		};

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_TextNatives);
			return true;
		}

		namespace API
		{
			static cell_t TransformFromGBKToUTF8(IPluginContext* pContext, const cell_t* params)
			{
#ifdef _WIN32
				std::string in;
				sm::interop::cell2native(pContext, params[1], in);
				std::string out = vec::text::TransformFromGBKToUTF8(in);
				return pContext->StringToLocalUTF8(params[2], params[3], out.c_str(), nullptr);
#else
#endif // _WIN32

			}

			static cell_t TransformFromUTF8ToGBK(IPluginContext* pContext, const cell_t* params)
			{
#ifdef _WIN32
				std::string in;
				sm::interop::cell2native(pContext, params[1], in);
				std::string out = vec::text::TransformFromUTF8ToGBK(in);
				return pContext->StringToLocalUTF8(params[2], params[3], out.c_str(), nullptr);
#else
#endif // _WIN32

			}
		}
	}
}