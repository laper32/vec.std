#include "tools.h"

namespace vec
{
	namespace tools
	{
		sp_nativeinfo_t g_ToolNatives[] = {
			{"ToolsSetVelocity",					API::SetVelocity},
			{"ToolsGetVelocity",					API::GetVelocity},
			{"ToolsGetSpeed",						API::GetSpeed},
			{"ToolsGetAbsOrigin",					API::GetAbsOrigin},
			{"ToolsGetAbsAngles",					API::GetAbsAngles},
			{"ToolsGetMyWeapons",					API::GetMyWeapons},
			{"ToolsGetWeapon",						API::GetWeapon},
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
			{"ToolsGetActiveWeapon",				API::GetActiveWeapon},
			{"ToolsSetActiveWeapon",				API::SetActiveWeapon},
			{"ToolsGetAddonBits",					API::GetAddonBits},
			{"ToolsSetAddonBits",					API::SetAddonBits},
			{"ToolsGetObserverMode",				API::GetObserverMode},
			{"ToolsGetObserverTarget",				API::GetObserverTarget},
			{"ToolsGetHitGroup",					API::GetHitGroup},
			{"ToolsGetScore",						API::GetScore},
			{"ToolsSetScore",						API::SetScore},
			{"ToolsGetFrags",						API::GetFrags},
			{"ToolsSetFrags",						API::SetFrags},
			{"ToolsGetDeaths",						API::GetDeaths},
			{"ToolsSetDeaths",						API::SetDeaths},
			{"ToolsGetGravity",						API::GetGravity},
			{"ToolsSetGravity",						API::SetGravity},
			{"ToolsSetSpot",						API::SetSpot},
			{"ToolsSetDetecting",					API::SetDetecting},
			{"ToolsSetHud",							API::SetHud},
			{"ToolsGetArm",							API::GetArm},
			{"ToolsSetArm",							API::SetArm},
			{"ToolsSetAttack",						API::SetAttack},
			{"ToolsSetFlashLight",					API::SetFlashLight},
			{"ToolsSetFov",							API::SetFov},
			{"ToolsSetTextures",					API::SetTextures},
			{"ToolsGetEffect",						API::GetEffect},
			{"ToolsSetEffect",						API::SetEffect},
			{"ToolsGetActivator",					API::GetActivator},
			{"ToolsSetModelIndex",					API::SetModelIndex},
			{"ToolsGetOwner",						API::GetOwner},
			{"ToolsSetOwner",						API::SetOwner},
			{"ToolsGetParent",						API::GetParent},
			{"ToolsSetParent",						API::SetParent},
			{"ToolsGetRagdollIndex",				API::GetRagdollIndex},
			{"ToolsGetCollisionGroup",				API::GetCollisionGroup},
			{"ToolsSetCollisionGroup",				API::SetCollisionGroup},
			{"ToolsSetProgressBarTime",				API::SetProgressBarTime},
			{"ToolsResetProgressBarTime",			API::ResetProgressBarTime},
			{"ToolsGetMaxs",						API::GetMaxs},
			{"ToolsGetMins",						API::GetMins},
			{"ToolsGetModelName",					API::GetModelName},
			{"ToolsGetEntityKeyValue",				API::GetEntityKeyValue},
			{nullptr, nullptr}
		};
		
		

		void OnClientInit(int client)
		{

		}

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_ToolNatives);

			return true;
		}

		namespace API
		{
			static cell_t SetVelocity(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				Vector in;
				sm::interop::cell2native(pContext, params[2], in);

				vec::tools::SetVelocity(entity, in, params[3], params[4]);
				return 1;
			}
			static cell_t GetVelocity(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				Vector pos = vec::tools::GetVelocity(entity);
				return sm::interop::native2cell(pContext, pos, params[2]);
			}
			static cell_t GetSpeed(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sp_ftoc(vec::tools::GetSpeed(entity));
			}
			static cell_t GetAbsOrigin(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				Vector pos = vec::tools::GetAbsOrigin(entity);
				return sm::interop::native2cell(pContext, pos, params[2]);
			}
			static cell_t GetAbsAngles(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				QAngle ang = vec::tools::GetAbsAngles(entity);
				return sm::interop::native2cell(pContext, ang, params[2]);
			}
			// 因为一些原因 (如ZP等), 我们必须用GetEntPropArraySize类似的方式
			// 如果只是DLL限定的话, 就无所谓了.
			static cell_t GetMyWeapons(IPluginContext* pContext, const cell_t* params) {
				int cnt = 0;
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}

				for (CBaseCombatWeapon* weapon : vec::tools::GetMyWeapons(player))
				{
					cnt++;
				}
				return cnt;
			}
			// keeps in there...
			static cell_t GetWeapon(IPluginContext* pContext, const cell_t* params) {
				int pos = params[2];
				int cnt = 0;
				int out = -1;
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}

				for (CBaseCombatWeapon* weapon : vec::tools::GetMyWeapons(player))
				{
					cnt++;
					if (cnt == pos) out = sm::ent_cast<int>(weapon); break;
				}
				return out;
			}
			static cell_t GetHealth(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetHealth(entity, params[2]);
			}
			static cell_t SetHealth(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetHealth(entity, params[2], params[3]);
				return 0;
			}
			static cell_t GetLMV(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sp_ftoc(vec::tools::GetLMV(entity));
			}
			static cell_t SetLMV(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetLMV(entity, sp_ctof(params[2]));
				return 0;
			}
			static cell_t GetArmor(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetArmor(entity);
			}
			static cell_t SetArmor(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetArmor(entity, params[2]);
				return 0;
			}
			static cell_t GetTeam(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetTeam(entity);
			}
			static cell_t SetTeam(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetTeam(entity, static_cast<CSTeam_e>(params[2]));
				return 0;
			}
			static cell_t GetNightVision(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetNightVision(entity, params[2]);
			}
			static cell_t SetNightVision(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetNightVision(entity, params[2], params[3]);
				return 0;
			}
			static cell_t GetDefuser(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetDefuser(entity);
			}
			static cell_t SetDefuser(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetDefuser(entity, params[2]);
				return 0;
			}
			// WARNING: When using, only accepted player entity index is in the bound of 1~MaxClients
			// or will crash the server!
			static cell_t GetHelmet(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetHelmet(entity);
			}
			static cell_t SetHelmet(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetHelmet(entity, params[2]);
				return 0;
			}
			static cell_t GetHeavySuit(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetHeavySuit(entity);
			}
			static cell_t SetHeavySuit(IPluginContext* pContext, const cell_t* params) {

				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetHeavySuit(entity, params[2]);
				return 0;
			}
			static cell_t GetActiveWeapon(IPluginContext* pContext, const cell_t* params) {
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return -1;
				}
				return sm::ent_cast<cell_t>(vec::tools::GetActiveWeapon(player));
			}
			static cell_t SetActiveWeapon(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetAddonBits(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetAddonBits(entity);
			}
			static cell_t SetAddonBits(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetAddonBits(entity, params[2]);
				return 0;
			}
			static cell_t GetObserverMode(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetObserverMode(entity);
			}
			static cell_t GetObserverTarget(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sm::ent_cast<cell_t>(vec::tools::GetObserverTarget(entity));
			}
			static cell_t GetHitGroup(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetHitGroup(entity);
			}
			static cell_t GetScore(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetScore(entity, params[2]);
			}
			static cell_t SetScore(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetScore(entity, params[2], params[3]);
				return 0;
			}
			static cell_t GetFrags(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetFrags(entity);
			}
			static cell_t SetFrags(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetFrags(entity, params[2]);
				return 0;
			}
			static cell_t GetDeaths(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetDeaths(entity);
			}
			static cell_t SetDeaths(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetDeaths(entity, params[2]);
				return 0;
			}
			static cell_t GetGravity(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sp_ftoc(vec::tools::GetGravity(entity));
			}
			static cell_t SetGravity(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetGravity(entity, sp_ctof(params[2]));
				return 0;
			}
			static cell_t SetSpot(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetSpot(entity, params[2]);
				return 0;
			}
			static cell_t SetDetecting(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetDetecting(entity, params[2]);
				return 0;
			}
			static cell_t SetHud(IPluginContext* pContext, const cell_t* params) {
				return 0;
			}
			static cell_t GetArm(IPluginContext* pContext, const cell_t* params) {
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}
				const char* name = sm::GetEntPropString(player, sm::Prop_Send, "m_szArmsModel");
				return pContext->StringToLocalUTF8(params[2], params[3], name, nullptr);
			}
			static cell_t SetArm(IPluginContext* pContext, const cell_t* params) {
				std::string out;
				sm::interop::cell2native(pContext, params[2], out);
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}
				char* mdlpath = {};
				strcpy(mdlpath, out.c_str());
				vec::tools::SetArm(player, mdlpath);
				return 0;
			}
			static cell_t SetAttack(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetAttack(entity, sp_ctof(params[2]));
				return 0;
			}
			static cell_t SetFlashLight(IPluginContext* pContext, const cell_t* params) {
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetFlashLight(player, params[2]);
				return 0;
			}
			static cell_t SetFov(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetFov(entity, params[2]);
				return 0;
			}
			static cell_t SetTextures(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetTextures(entity, params[2], params[3]);
				return 0;
			}
			static cell_t GetEffect(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetEffect(entity);
			}
			static cell_t SetEffect(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetEffect(entity, params[2]);
				return 0;
			}
			static cell_t GetActivator(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sm::ent_cast<cell_t>(vec::tools::GetActivator(entity));
			}
			static cell_t SetModelIndex(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetModelIndex(entity, params[2]);
				return 0;
			}
			static cell_t GetOwner(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sm::ent_cast<cell_t>(vec::tools::GetOwner(entity));
			}
			static cell_t SetOwner(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}

				CBaseEntity* owner = sm::ent_cast<CBaseEntity*>(params[2]);
				if (!owner)
				{
					pContext->ReportError("Owner is nullptr. Index: %d", params[2]);
					return 0;
				}

				vec::tools::SetOwner(entity, owner);
				return 0;
			}
			static cell_t GetParent(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return sm::ent_cast<cell_t>(vec::tools::GetParent(entity));
			}
			static cell_t SetParent(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}

				CBaseEntity* parent = sm::ent_cast<CBaseEntity*>(params[2]);
				if (!parent)
				{
					pContext->ReportError("Parent is nullptr. Index: %d", params[2]);
					return 0;
				}

				vec::tools::SetParent(entity, parent);
				return 0;
			}
			static cell_t GetRagdollIndex(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetRagdollIndex(entity);
			}
			static cell_t GetCollisionGroup(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				return vec::tools::GetCollisionGroup(entity);
			}
			static cell_t SetCollisionGroup(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetCollisionGroup(entity, params[2]);
				return 0;
			}
			static cell_t SetProgressBarTime(IPluginContext*pContext, const cell_t* params) {
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::SetProgressBarTime(player, params[2]);
				return 0;
			}
			static cell_t ResetProgressBarTime(IPluginContext* pContext, const cell_t* params) {
				CBasePlayer* player = sm::ent_cast<CBasePlayer*>(params[1]);
				if (!player)
				{
					pContext->ReportError("Player is nullptr. Index: %d", params[1]);
					return 0;
				}
				vec::tools::ResetProgressBarTime(player);
				return 0;
			}
			static cell_t GetMaxs(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				Vector maxs = vec::tools::GetMaxs(entity);
				return sm::interop::native2cell(pContext, maxs, params[2]);
			}
			static cell_t GetMins(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				Vector mins = vec::tools::GetMins(entity);
				return sm::interop::native2cell(pContext, mins, params[2]);
			}
			static cell_t GetModelName(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return 0;
				}
				const char* name = vec::tools::GetModelName(entity);
				return pContext->StringToLocalUTF8(params[2], params[3], name, nullptr);
			}
			static cell_t GetEntityKeyValue(IPluginContext* pContext, const cell_t* params) {
				CBaseEntity* entity = sm::ent_cast<CBaseEntity*>(params[1]);
				if (!entity)
				{
					pContext->ReportError("Entity is nullptr. Index: %d", params[1]);
					return false;
				}
				std::string key;
				sm::interop::cell2native(pContext, params[2], key);
				char output[512];
				sm::sdktools::servertools->GetKeyValue(entity, key.c_str(), output, sizeof(output));
				return pContext->StringToLocalUTF8(params[3], params[4], output, nullptr);
			}
		}
	}
}