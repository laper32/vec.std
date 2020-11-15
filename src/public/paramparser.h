/**
 * Provides functions for parsing single line strings, and parameters in key = "value" format.
 *
 * Example:
 *			key1 = "value1"
 *			key2 = "value2", "value3"
 *			key3 = "value4", "value5", "value6"
 *			key4 = "value7"
 */

#pragma once

#include <string>
#include <algorithm>
#include "extension.h"

namespace vec
{
	namespace paramparser
	{

		constexpr auto PARAM_ERROR_NO = -1;					// No errors. 
		constexpr auto PARAM_ERROR_EMPTY = 0;				// Source string is empty. 
		constexpr auto PARAM_ERROR_UNEXPECTED_KEY = 1;		// Unexpected key name. 
		constexpr auto PARAM_ERROR_UNEXPECTED_END = 2;		// Unexpected end of source string. 
		constexpr auto PARAM_ERROR_MISSING_SEPARATOR = 3;   // Could not find a separator sign after key name. 
		constexpr auto PARAM_ERROR_MISSING_QUOTES = 4;		// Could not find a quotes sign (") after key name. 
		constexpr auto PARAM_ERROR_UNKNOWN = 5;				// Unknown error. The parser got a invalid result from
													// a search function it couldn't handle. 
		constexpr auto PARAM_ERROR_FULL = 6;				// Destination array is full. 

		const char param_error[7][256] =
		{
			//"No errors",
			"Source string is empty",
			"Unexpected key name",
			"Unexpected end of source string",
			"Could not find a separator sign after key name",
			"Could not find a quotes sign (\") after key name",
			"Unknown error. The parser got a invalid result from a search function it couldn't handle",
			"Destination array is full"
		};
	}
}