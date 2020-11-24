#pragma once

// N->Not test yet
// Y->Tested

/*
ToolsSetVelocity
ToolsGetVelocity
ToolsGetSpeed
ToolsGetAbsOrigin
ToolsGetAbsAngles
ToolsGetMyWeapons
ToolsGetWeapon
ToolsGetHealth
ToolsSetHealth
ToolsGetLMV
ToolsSetLMV
ToolsGetArmor
ToolsSetArmor
ToolsGetTeam
ToolsSetTeam
ToolsGetNightVision
ToolsSetNightVision
ToolsGetDefuser
ToolsSetDefuser
ToolsGetHelmet
ToolsSetHelmet
ToolsGetHeavySuit
ToolsSetHeavySuit
ToolsGetActiveWeapon
ToolsSetActiveWeapon
ToolsGetAddonBits
ToolsSetAddonBits
ToolsGetObserverMode
ToolsGetObserverTarget
ToolsGetHitGroup
ToolsGetScore
ToolsSetScore
ToolsSetGravity
ToolsSetSpot
ToolsSetDetecting
ToolsSetHud
ToolsSetArm
ToolsSetAttack
ToolsSetFlashLight
ToolsSetFov
ToolsSetTextures
ToolsGetEffect
ToolsSetEffect
ToolsGetActivator
ToolsSetModelIndex
ToolsGetOwner
ToolsSetOwner
ToolsGetParent
ToolsSetParent
ToolsGetRagdollIndex
ToolsGetCollisionGroup
ToolsSetCollisionGroup
*/

#ifndef _VEC_STD_TOOLS_H_
#define _VEC_STD_TOOLS_H_

#include "extension.h"
#include <sm/cstrike.h>
#include <sm/sourcemod.h>
#include <sm/sdktools.h>
#include <vector>
#include <algorithm>
#include <ranges>

namespace vec
{
	namespace tools
	{
		// core caller
		sp_nativeinfo_t g_ToolNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);

		// API extern
		namespace API
		{
			static cell_t GetTeam(IPluginContext*, const cell_t*);
		}

		// Header-SDK Functions.

		//N
		inline Vector GetVelocity(CBaseEntity* pEntity)
		{
			return sm::GetEntProp<Vector>(pEntity, sm::Prop_Data, "m_vecVelocity");
		}

		//N
		inline void SetVelocity(CBaseEntity* pEntity, Vector vVelocity, bool bApply = true, bool bStack = true)
		{
			if (!bApply) vVelocity = GetVelocity(pEntity); return;

			if (bStack) vVelocity += GetVelocity(pEntity);

			sm::sdktools::TeleportEntity(pEntity, {}, {}, vVelocity);
		}

		//N
		inline float GetSpeed(CBaseEntity* pEntity)
		{
			Vector vel = GetVelocity(pEntity);
			return vel.Length();
		}

		//Y
		inline Vector GetAbsOrigin(CBaseEntity* pEntity)
		{
			return sm::GetEntProp<Vector>(pEntity, sm::Prop_Data, "m_vecAbsOrigin");
		}

		//Y
		inline Vector GetAbsAngles(CBaseEntity* pEntity)
		{
			return sm::GetEntProp<Vector>(pEntity, sm::Prop_Data, "m_angAbsRotation");
		}
		
		//N
		inline CBaseCombatWeapon* GetActiveWeapon(CBasePlayer* entity)
		{
			return static_cast<CBaseCombatWeapon*>(
				sm::ent_cast<CBaseEntity*>(sm::GetEntProp<CBaseHandle>(entity, sm::Prop_Send, "m_hActiveWeapon"))
				);
		}

		//N
		inline auto GetMyWeapons(CBasePlayer* entity)
		{
			// ignore this warning
			return sm::GetEntPropArray<CBaseHandle>(entity, sm::Prop_Data, "m_hMyWeapons")
				| std::ranges::views::transform(sm::Converter<CBaseCombatWeapon*>())
				| std::ranges::views::filter(std::identity());
		}

		//Y
		inline int GetTeam(CBaseEntity* entity) {
			return sm::GetEntProp<int>(entity, sm::Prop_Data, "m_iTeamNum");
		}

		//N
		inline void SetTeam(CBaseEntity* entity, CSTeam_e iValue)
		{
			// Validate team
			if (iValue <= CS_TEAM_SPECTATOR) /// Fix, thanks to inklesspen!
			{
				// Sets team of the entity
				sm::sourcemod::ChangeClientTeam(playerhelpers->GetGamePlayer(gamehelpers->EntityToReference(entity)), iValue);
			}
			else
			{
				// Switch team of the entity
				sm::cstrike::CS_SwitchTeam(sm::ent_cast<CBasePlayer*>(entity), iValue);
			}
		}

		//Y
		inline int GetFrags(CBaseEntity* entity) {
			return sm::GetEntProp<int>(entity, sm::Prop_Data, "m_iFrags");
		}

		//Y
		inline void SetFrags(CBaseEntity* entity, int value)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Data, "m_iFrags", value);
		}

		//Y
		inline int GetDeaths(CBaseEntity* entity)
		{
			return sm::GetEntProp<int>(entity, sm::Prop_Data, "m_iDeaths");
		}

		//Y
		inline void SetDeaths(CBaseEntity* entity, int value)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Data, "m_iDeaths", value);
		}

		//Y
		inline bool GetDefuser(CBaseEntity* entity)
		{
			return sm::GetEntProp<bool>(entity, sm::Prop_Send, "m_bHasDefuser");
		}

		//Y
		inline void SetDefuser(CBaseEntity* entity, bool bEnable)
		{
			sm::SetEntProp<bool>(entity, sm::Prop_Send, "m_bHasDefuser", bEnable);
		}

		//Y
		inline int GetHealth(CBaseEntity* entity, bool bMax = false)
		{
			return sm::GetEntProp<int>(entity, sm::Prop_Data, bMax ? "m_iMaxHealth" : "m_iHealth");
		}

		//Y
		inline void SetHealth(CBaseEntity* entity, int iValue, bool bSet = false)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Send, "m_iHealth", iValue);
			if (bSet) sm::SetEntProp<int>(entity, sm::Prop_Data, "m_iMaxHealth", iValue);
		}

		//Y
		inline int GetArmor(CBaseEntity* entity)
		{
			return sm::GetEntProp<int>(entity, sm::Prop_Send, "m_ArmorValue");
		}

		//Y
		inline void SetArmor(CBaseEntity* entity, int iValue)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Send, "m_ArmorValue", iValue);
		}

		//Y
		inline float GetLMV(CBaseEntity* entity)
		{
			return sm::GetEntProp<float>(entity, sm::Prop_Send, "m_flLaggedMovementValue");
		}

		//Y
		inline void SetLMV(CBaseEntity* entity, float flValue)
		{
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flLaggedMovementValue", flValue);
		}

		//Y
		inline float GetGravity(CBaseEntity* entity)
		{
			return sm::GetEntProp<float>(entity, sm::Prop_Send, "m_flGravity");
		}

		//Y
		inline void SetGravity(CBaseEntity* entity, float flValue)
		{
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flGravity", flValue);
		}

		//Y
		inline bool GetHelmet(CBaseEntity* entity)
		{
			return sm::GetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHelmet");
		}

		//Y
		inline void SetHelmet(CBaseEntity* entity, bool bEnable)
		{
			sm::SetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHelmet", bEnable);
		}

		//Y
		inline bool GetHeavySuit(CBaseEntity* entity)
		{
			return sm::GetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHeavyArmor");
		}
		//Y
		inline void SetHeavySuit(CBaseEntity* entity, bool bEnable) {
			sm::SetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHeavyArmor", bEnable);
		}
		//Y
		inline bool GetNightVision(CBaseEntity* pEntity, bool ownership = false) {
			return sm::GetEntProp<bool>(pEntity, sm::Prop_Send, ownership ? "m_bHasNightVision" : "m_bNightVisionOn");
		}
		//Y
		inline void SetNightVision(CBaseEntity* pEntity, bool enable, bool ownership = false) {
			sm::SetEntProp<bool>(pEntity, sm::Prop_Send, ownership ? "m_bHasNightVision" : "m_bNightVisionOn", enable);
		}
		//N
		inline int GetAddonBits(CBaseEntity* pEntity) {
			return sm::GetEntProp<int>(pEntity, sm::Prop_Send, "m_iAddonBits");
		}
		//N
		inline int SetAddonBits(CBaseEntity* pEntity, int val) {
			sm::SetEntProp<int>(pEntity, sm::Prop_Send, "m_iAddonBits", val);
		}
		//N
		inline int GetObserverMode(CBaseEntity* pEntity) {
			return sm::GetEntProp<int>(pEntity, sm::Prop_Data, "m_iObserverMode");
		}
		//N
		inline CBaseEntity* GetObserverTarget(CBaseEntity* entity) {
			return sm::ent_cast<CBaseEntity*>(sm::GetEntProp<CBaseHandle>(entity, sm::Prop_Send, "m_hObserverTarget"));
		}
		//N
		inline int GetHitGroup(CBaseEntity* pEntity) {
			return sm::GetEntProp<int>(pEntity, sm::Prop_Send, "m_LastHitGroup");
		}
		//N
		inline void SetDetecting(CBaseEntity* pEntity, bool enable) {
			sm::SetEntProp<float>(pEntity, sm::Prop_Send, "m_flDetectedByEnemySensorTime", enable ? (gpGlobals->curtime + 9999.f) : 0.f);
		}
		//N
		inline void SetArms(CBasePlayer* entity, const char* path)
		{
			sm::SetEntProp<const char*>(entity, sm::Prop_Send, "m_szArmsModel", path);
		}
		//N
		inline void SetAttack(CBaseEntity* entity, float val) {
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flNextAttack", val);
		}
		//N
		inline void SetFov(CBaseEntity* pEntity, int val = 90) {
			sm::SetEntProp<int>(pEntity, sm::Prop_Send, "m_iFOV", val);
			sm::SetEntProp<int>(pEntity, sm::Prop_Send, "m_iDefaultFOV", val);
		}
		//N
		inline void SetTexture(CBaseEntity* ent, int body = -1, int skin = -1) {
			if (body != -1) sm::SetEntProp<int>(ent, sm::Prop_Send, "m_nBody", body);
			if (skin != -1) sm::SetEntProp<int>(ent, sm::Prop_Send, "m_nSkin", skin);
		}
		//N
		inline int GetEffect(CBaseEntity* ent) {
			return sm::GetEntProp<int>(ent, sm::Prop_Send, "m_fEffects");
		}
		//N
		inline void SetEffect(CBaseEntity* ent, int val) {
			sm::SetEntProp<int>(ent, sm::Prop_Send, "m_fEffects", val);
		}
		//N
		inline void SetFlashlight(CBasePlayer* ent, bool enable) {
			SetEffect(ent, enable ? (GetEffect(ent) ^ EF_DIMLIGHT) : 0);
		}
		//N
		inline CBasePlayer* GetActivator(CBaseEntity* pEntity) {
			return sm::ent_cast<CBasePlayer*>(sm::GetEntProp<CBaseHandle>(pEntity, sm::Prop_Data, "m_pActivator"));
		}
		//N
		inline void SetModelIndex(CBaseEntity* ent, int mdl) {
			sm::SetEntProp<int>(ent, sm::Prop_Send, "m_nModelIndex", mdl);
		}
		//N
		inline CBaseEntity* GetOwner(CBaseEntity* ent, int mdl) {
			return sm::ent_cast<CBaseEntity*>(sm::GetEntProp<CBaseHandle>(ent, sm::Prop_Data, "m_hOwner"));
		}
		//N
		inline void SetOwner(CBaseEntity* ent, CBaseEntity* owner) {
			sm::SetEntProp<CBaseEntity*>(ent, sm::Prop_Data, "m_hOwner", owner);
		}
		//N
		inline CBaseEntity* GetParent(CBaseEntity* ent) {
			return sm::ent_cast<CBaseEntity*>(sm::GetEntProp<CBaseHandle>(ent, sm::Prop_Send, "m_pParent"));
		}
		//N
		inline CBaseEntity* SetParent(CBaseEntity* ent, CBaseEntity* parent) {
			sm::SetEntProp<CBaseEntity*>(ent, sm::Prop_Send, "m_pParent", parent);
		}
		//N
		inline int GetRagdollIndex(CBaseEntity* pEntity) {
			return sm::ent_cast<int>(sm::GetEntProp<CBaseHandle>(pEntity, sm::Prop_Send, "m_hRagdoll"));
		}
		//N
		inline int GetCollisionGroup(CBaseEntity* ent) {
			return sm::GetEntProp<int>(ent, sm::Prop_Data, "m_CollisionGroup");
		}
		//N
		inline void SetCollisionGroup(CBaseEntity* ent, int val) {
			sm::SetEntProp<int>(ent, sm::Prop_Data, "m_CollisionGroup", val);
		}
	}
}

#endif // !_VEC_STD_TOOLS_H_