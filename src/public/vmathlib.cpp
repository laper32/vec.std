#include "vmathlib.h"
#include <sstream>
namespace vec
{
	namespace mathlib
	{
		sp_nativeinfo_t g_vMathLibNatives[] = {
			{"GetAliasMethodValue",						API::GetAliasMethodValue},
			{"GetPresudoExponentialDistributionValue",	API::GetPresudoExponentialDistributionValue},
			{"GetPresudoExponentialDistributionValue2", API::GetPresudoExponentialDistributionValue2},
			{nullptr,									nullptr}
		};
		
		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_vMathLibNatives);
			return true;
		}
		
		// Only accepts "xx xx xx xx"
		template<typename T>
		std::vector<T> string2vector(std::string in)
		{
			T buffer = {};
			std::stringstream ss(in);
			std::vector<T> Ret;

			while (ss >> buffer)
				Ret.push_back(buffer);
			return Ret;
		}

		namespace API
		{
			static cell_t GetAliasMethodValue(IPluginContext* pContext, const cell_t* params)
			{
				std::string probStr;
				sm::interop::cell2native(pContext, params[1], probStr);

				std::vector<float> probList = string2vector<float>(probStr);
				if (!probList.size())
				{
					pContext->ReportError("probability list is empty. Check input: %s", probStr.c_str());
					return -1;
				}
				AliasMethod method(probList);
				return method.Get();
			}
			static cell_t GetPresudoExponentialDistributionValue(IPluginContext* pContext, const cell_t* params)
			{
				cell_t rate = params[1];
				if (rate <= 0)
				{
					pContext->ReportError("Invalid rate input: %d", rate);
					return -1;
				}
				return vec::mathlib::GetPresudoExponentialDistributionValue(rate);
			}
			static cell_t GetPresudoExponentialDistributionValue2(IPluginContext* pContext, const cell_t* params)
			{
				cell_t rate = params[1];
				if (rate <= 0)
				{
					pContext->ReportError("Invalid rate input: %d", rate);
					return -1;
				}
				cell_t maxIterCount = params[2];

				if (!maxIterCount)
				{
					pContext->ReportError("Maximum iter cannot be 0");
					return -1;
				}

				if (rate < 0)
				{
					pContext->ReportError("Maximum iterate count must unsigned (Have transfer to + to avoid crash): %d.", maxIterCount);
					maxIterCount = std::abs(maxIterCount);
				}

				return vec::mathlib::GetPresudoExponentialDistributionValue2(rate, maxIterCount);
			}
		}
	}
}