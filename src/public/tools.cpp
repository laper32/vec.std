#include "tools.h"

namespace vec
{
	namespace tools
	{
		sp_nativeinfo_t g_ToolNatives[] = {
			{"ToolsSetVelocity",					API::SetVelocity},
			{"ToolsGetVelocity",					API::GetVelocity},
			{"ToolsGetSpeed",						API::GetSpeed},
			{"ToolsGetTeam",						API::GetTeam},
			{"ToolsGetAbsOrigin",					API::GetAbsOrigin},
			{"ToolsGetAbsAngles",					API::GetAbsAngles},
			//{"ToolsGetMyWeapons",					API::GetMyWeapons},
			//{"ToolsGetWeapon",					API::GetWeapon},
			{"ToolsGetHealth",						API::GetHealth},
			{"ToolsSetHealth",						API::SetHealth},
			{"ToolsGetLMV",							API::GetLMV},
			{"ToolsSetLMV",							API::SetLMV},
			{"ToolsGetArmor",						API::GetArmor},
			{"ToolsSetArmor",						API::SetArmor},
			{"ToolsGetTeam",						API::GetTeam},
			{"ToolsSetTeam",						API::SetTeam},
			{"ToolsGetNightVision",					API::GetNightVision},
			{"ToolsSetNightVision",					API::SetNightVision},
			{"ToolsGetDefuser",						API::GetDefuser},
			{"ToolsSetDefuser",						API::SetDefuser},
			{"ToolsGetHelmet",						API::GetHelmet},
			{"ToolsSetHelmet",						API::SetHelmet},
			{"ToolsGetHeavySuit",					API::GetHeavySuit},
			{"ToolsSetHeavySuit",					API::SetHeavySuit},
			//{"ToolsGetActiveWeapon",				API::GetActiveWeapon},
			//{"ToolsSetActiveWeapon",				API::SetActiveWeapon},
			{"ToolsGetAddonBits",					API::GetAddonBits},
			{"ToolsSetAddonBits",					API::SetAddonBits},
			//{"ToolsGetObserverMode",				API::GetObserverMode},
			//{"ToolsGetObserverTarget",			API::GetObserverTarget},
			{"ToolsGetHitGroup",					API::GetHitGroup},
			{"ToolsGetFrags",						API::GetFrags},
			{"ToolsSetFrags",						API::SetFrags},
			{"ToolsGetDeaths",						API::GetDeaths},
			{"ToolsSetDeaths",						API::SetDeaths},
			{"ToolsSetGravity",						API::SetGravity},
			//{"ToolsSetSpot",						API::SetSpot},
			{"ToolsSetDetecting",					API::SetDetecting},
			//{"ToolsSetHud",						API::SetHud},
			//{"ToolsSetArm",						API::SetArm},
			{"ToolsSetAttack",						API::SetAttack},
			{"ToolsSetFlashLight",					API::SetFlashLight},
			{"ToolsSetFov",							API::SetFov},
			{"ToolsSetTextures",					API::SetTextures},
			{"ToolsGetEffect",						API::GetEffect},
			{"ToolsSetEffect",						API::SetEffect},
			//{"ToolsGetActivator",					API::GetActivator},
			{"ToolsSetModelIndex",					API::SetModelIndex},
			//{"ToolsGetOwner",						API::GetOwner},
			//{"ToolsSetOwner",						API::SetOwner},
			//{"ToolsGetParent",					API::GetParent},
			//{"ToolsSetParent",					API::SetParent},
			//{"ToolsGetRagdollIndex",				API::GetRagdollIndex},
			{"ToolsGetCollisionGroup",				API::GetCollisionGroup},
			{"ToolsSetCollisionGroup",				API::SetCollisionGroup},
			{nullptr, nullptr}
		};

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			g_pShareSys->AddNatives(myself, g_ToolNatives);
			//sharesys->AddNatives(myself, g_ToolsNative);

			return true;
		}

		namespace API
		{
			// HELP
			static cell_t SetVelocity(IPluginContext* pContext, const cell_t* params) {
				
				//auto [pEntity, velocity, apply, stack] = sm::interop::params2tuple<CBaseEntity*, Vector, bool, bool>(pContext, params);
				//vec::tools::SetVelocity(pEntity, velocity, apply, stack);
				return 1;
			}
			static cell_t GetVelocity(IPluginContext* pContext, const cell_t* params) {
				Vector out = vec::tools::GetVelocity(sm::ent_cast<CBaseEntity*>(params[1]));
				return sm::interop::cell2native(pContext, params[2], out);
			}
			static cell_t GetSpeed(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetSpeed(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t GetAbsOrigin(IPluginContext* pContext, const cell_t* params) {
				Vector out = vec::tools::GetAbsOrigin(sm::ent_cast<CBaseEntity*>(params[1]));
				return sm::interop::cell2native(pContext, params[2], out);
			}
			static cell_t GetAbsAngles(IPluginContext* pContext, const cell_t* params) {
				Vector out = vec::tools::GetAbsAngles(sm::ent_cast<CBaseEntity*>(params[1]));
				sm::interop::cell2native(pContext, params[2], out);
			}
			// wait a sec here..
			static cell_t GetMyWeapons(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetWeapon(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetHealth(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetHealth(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetHealth(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetHealth(sm::ent_cast<CBaseEntity*>(params[1]), params[2], params[3]);
				return 0;
			}
			static cell_t GetLMV(IPluginContext* pContext, const cell_t* params) {
				return sp_ftoc(vec::tools::GetLMV(sm::ent_cast<CBaseEntity*>(params[1])));
			}
			static cell_t SetLMV(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetLMV(sm::ent_cast<CBaseEntity*>(params[1]), sp_ctof(params[2]));
				return 0;
			}
			static cell_t GetArmor(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetArmor(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetArmor(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetArmor(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetTeam(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetTeam(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetTeam(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetTeam(sm::ent_cast<CBaseEntity*>(params[1]), static_cast<CSTeam_e>(params[2]));
				return 0;
			}
			static cell_t GetNightVision(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetNightVision(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
			}
			static cell_t SetNightVision(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetNightVision(sm::ent_cast<CBaseEntity*>(params[1]), params[2], params[3]);
				return 0;
			}
			static cell_t GetDefuser(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetDefuser(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetDefuser(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetDefuser(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			// WARNING: When using, only accepted player entity index is in the bound of 1~MaxClients
			// or will crash the server!
			static cell_t GetHelmet(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetHelmet(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetHelmet(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetHelmet(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetHeavySuit(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetHeavySuit(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetHeavySuit(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetHeavySuit(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetActiveWeapon(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetActiveWeapon(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetAddonBits(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetAddonBits(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetAddonBits(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetAddonBits(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetObserverMode(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetObserverMode(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t GetObserverTarget(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetHitGroup(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetHitGroup(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t GetFrags(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetFrags(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetFrags(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetFrags(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetDeaths(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetDeaths(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetDeaths(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetDeaths(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t SetGravity(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetGravity(sm::ent_cast<CBaseEntity*>(params[1]), sp_ctof(params[2]));
				return 0;
			}
			static cell_t SetSpot(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetDetecting(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetDetecting(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t SetHud(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetArm(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetAttack(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetAttack(sm::ent_cast<CBaseEntity*>(params[1]), sp_ctof(params[2]));
				return 0;
			}
			static cell_t SetFlashLight(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetFlashLight(sm::ent_cast<CBasePlayer*>(params[1]), params[2]);
				return 0;
			}
			static cell_t SetFov(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetFov(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t SetTextures(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetTextures(sm::ent_cast<CBaseEntity*>(params[1]), params[2], params[3]);
				return 0;
			}
			static cell_t GetEffect(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetEffect(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetEffect(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetEffect(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetActivator(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetModelIndex(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetModelIndex(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
			static cell_t GetOwner(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetOwner(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetParent(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t SetParent(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetRagdollIndex(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetCollisionGroup(IPluginContext* pContext, const cell_t* params) {
				return vec::tools::GetCollisionGroup(sm::ent_cast<CBaseEntity*>(params[1]));
			}
			static cell_t SetCollisionGroup(IPluginContext* pContext, const cell_t* params) {
				vec::tools::SetCollisionGroup(sm::ent_cast<CBaseEntity*>(params[1]), params[2]);
				return 0;
			}
		}
	}
}