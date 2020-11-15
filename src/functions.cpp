#include "functions.h"

#include "public/tools.h"

namespace vec
{
	namespace functions
	{
		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			vec::tools::SDK_OnLoad(error, maxlen, late);
			return true;
		}
	}
}