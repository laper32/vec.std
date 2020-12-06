#include "functions.h"

#include "public/tools.h"
#include "public/engine.h"
#include "public/utils.h"
namespace vec
{
	namespace functions
	{
		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			vec::engine::SDK_OnLoad(error, maxlen, late);
			vec::tools::SDK_OnLoad(error, maxlen, late);
			vec::utils::SDK_OnLoad(error, maxlen, late);
			return true;
		}
	}
}