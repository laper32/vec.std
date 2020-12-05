#include "playermgr.h"
#include "sm/ranges.h"
namespace vec
{
	namespace playermgr
	{
		namespace API
		{
			static cell_t GetAliveCount(IPluginContext* pContext, const cell_t* params)
			{
				cell_t cnt = 0;

				//for (IGamePlayer* player : sm::ranges::Alive()) cnt++;
				
				return cell_t();
			}
		}
	}
}