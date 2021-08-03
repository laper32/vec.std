#pragma once

#ifndef _VEC_STD_TOOLS_H_
#define _VEC_STD_TOOLS_H_

#include "extension.h"

#include "sm/sourcemod.h"
#include "sm/cstrike.h"
#include "sm/sdktools.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include "engine.h"
#include "const.h"
#include "utils.h"
namespace vec
{
	namespace tools
	{
		// core caller
		sp_nativeinfo_t g_ToolNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);
		
		void OnClientInit(int client);

		// API extern
		namespace API
		{
			static cell_t SetVelocity(IPluginContext*, const cell_t*);
			static cell_t GetVelocity(IPluginContext*, const cell_t*);
			static cell_t GetSpeed(IPluginContext*, const cell_t*);
			static cell_t GetAbsOrigin(IPluginContext*, const cell_t*);
			static cell_t GetAbsAngles(IPluginContext*, const cell_t*);
			static cell_t GetMyWeapons(IPluginContext*, const cell_t*);
			static cell_t GetWeapon(IPluginContext*, const cell_t*);
			static cell_t GetHealth(IPluginContext*, const cell_t*);
			static cell_t SetHealth(IPluginContext*, const cell_t*);
			static cell_t GetLMV(IPluginContext*, const cell_t*);
			static cell_t SetLMV(IPluginContext*, const cell_t*);
			static cell_t GetArmor(IPluginContext*, const cell_t*);
			static cell_t SetArmor(IPluginContext*, const cell_t*);
			static cell_t GetTeam(IPluginContext*, const cell_t*);
			static cell_t SetTeam(IPluginContext*, const cell_t*);
			static cell_t GetNightVision(IPluginContext*, const cell_t*);
			static cell_t SetNightVision(IPluginContext*, const cell_t*);
			static cell_t GetDefuser(IPluginContext*, const cell_t*);
			static cell_t SetDefuser(IPluginContext*, const cell_t*);
			static cell_t GetHelmet(IPluginContext*, const cell_t*);
			static cell_t SetHelmet(IPluginContext*, const cell_t*);
			static cell_t GetHeavySuit(IPluginContext*, const cell_t*);
			static cell_t SetHeavySuit(IPluginContext*, const cell_t*);
			static cell_t GetActiveWeapon(IPluginContext*, const cell_t*);
			static cell_t SetActiveWeapon(IPluginContext*, const cell_t*);
			static cell_t GetAddonBits(IPluginContext*, const cell_t*);
			static cell_t SetAddonBits(IPluginContext*, const cell_t*);
			static cell_t GetObserverMode(IPluginContext*, const cell_t*);
			static cell_t GetObserverTarget(IPluginContext*, const cell_t*);
			static cell_t GetHitGroup(IPluginContext*, const cell_t*);
			static cell_t GetScore(IPluginContext*, const cell_t*);
			static cell_t SetScore(IPluginContext*, const cell_t*);
			static cell_t GetFrags(IPluginContext*, const cell_t*);
			static cell_t SetFrags(IPluginContext*, const cell_t*);
			static cell_t GetDeaths(IPluginContext*, const cell_t*);
			static cell_t SetDeaths(IPluginContext*, const cell_t*);
			static cell_t GetGravity(IPluginContext*, const cell_t*);
			static cell_t SetGravity(IPluginContext*, const cell_t*);
			static cell_t SetSpot(IPluginContext*, const cell_t*);
			static cell_t SetDetecting(IPluginContext*, const cell_t*);
			static cell_t SetHud(IPluginContext*, const cell_t*);
			static cell_t GetArm(IPluginContext*, const cell_t*);
			static cell_t SetArm(IPluginContext*, const cell_t*);
			static cell_t SetAttack(IPluginContext*, const cell_t*);
			static cell_t SetFlashLight(IPluginContext*, const cell_t*);
			static cell_t SetFov(IPluginContext*, const cell_t*);
			static cell_t SetTextures(IPluginContext*, const cell_t*);
			static cell_t GetEffect(IPluginContext*, const cell_t*);
			static cell_t SetEffect(IPluginContext*, const cell_t*);
			static cell_t GetActivator(IPluginContext*, const cell_t*);
			static cell_t SetModelIndex(IPluginContext*, const cell_t*);
			static cell_t GetOwner(IPluginContext*, const cell_t*);
			static cell_t SetOwner(IPluginContext*, const cell_t*);
			static cell_t GetParent(IPluginContext*, const cell_t*);
			static cell_t SetParent(IPluginContext*, const cell_t*);
			static cell_t GetRagdollIndex(IPluginContext*, const cell_t*);
			static cell_t GetCollisionGroup(IPluginContext*, const cell_t*);
			static cell_t SetCollisionGroup(IPluginContext*, const cell_t*);
			static cell_t SetProgressBarTime(IPluginContext*, const cell_t*);
			static cell_t ResetProgressBarTime(IPluginContext*, const cell_t*);
			static cell_t GetMaxs(IPluginContext*, const cell_t*);
			static cell_t GetMins(IPluginContext*, const cell_t*);
			static cell_t GetModelName(IPluginContext*, const cell_t*);
		}

		// Header-SDK Functions.

		/**
		 * @brief Gets the velocity of a entity.
		 *
		 * @param entity            The entity pointer.
		 * @return					The velocity vector.
		 */
		inline Vector GetVelocity(CBaseEntity* pEntity)
		{
			return sm::GetEntProp<Vector>(pEntity, sm::Prop_Data, "m_vecVelocity");
		}

		/**
		 * @brief Gets or sets the velocity of a entity.
		 *
		 * @param entity            The entity pointer.
		 * @param vVelocity         The velocity output, or velocity to set on entity.
		 * @param bApply            True to get entity velocity, false to set it.
		 * @param bStack            If modifying velocity, then true will stack new velocity onto the entity.
		 *                          current velocity, false will reset it.
		 */
		inline void SetVelocity(CBaseEntity* pEntity, Vector velocity, bool bApply = true, bool bStack = true)
		{
			if (!bApply) velocity = GetVelocity(pEntity); return;

			if (bStack)
			{
				Vector temp = GetVelocity(pEntity);
				velocity += temp;
			}

			sm::sdktools::TeleportEntity(pEntity, {}, {}, velocity);
		}

		/**
		 * @brief Gets the magnitude of velocity of a entity.
		 *
		 * @param entity            The entity pointer.
		 */
		inline float GetSpeed(CBaseEntity* pEntity)
		{
			Vector vel = GetVelocity(pEntity);
			return vel.Length();
		}

		/**
		 * @brief Gets the abs origin of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return					The origin vector.
		 */
		inline Vector GetAbsOrigin(CBaseEntity* pEntity)
		{
			return sm::GetEntProp<Vector>(pEntity, sm::Prop_Data, "m_vecAbsOrigin");
		}

		/**
		 * @brief Gets the abs angle of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return		            The angle vector.
		 */
		inline QAngle GetAbsAngles(CBaseEntity* pEntity)
		{
			return sm::GetEntProp<QAngle>(pEntity, sm::Prop_Data, "m_angAbsRotation");
		}

		/**
		 * @brief Gets the active weapon pointer of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The weapon ptr.
		 */
		inline CBaseCombatWeapon* GetActiveWeapon(CBasePlayer* entity)
		{
			return sm::GetEntPropEnt<CBaseCombatWeapon*>(entity, sm::Prop_Send, "m_hActiveWeapon");
		}
		/**
		 * @brief Sets the active weapon index of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param weapon            The weapon ptr.
		 */
		inline void SetActiveWeapon(CBasePlayer* entity, CBaseCombatWeapon* weapon)
		{
			sm::SetEntPropEnt(entity, sm::Prop_Send, "m_hActiveWeapon", weapon);
		}

		/**
		 * @brief Gets the weapons what this player owns.
		 *
		 * @param entity            The player pointer.
		 * @return                  the max weapons vector.
		 */
		inline auto GetMyWeapons(CBasePlayer* entity)
		{
			// ignore this warning
			return sm::GetEntPropArray<CBaseHandle>(entity, sm::Prop_Data, "m_hMyWeapons")
				| std::ranges::views::transform(sm::Converter<CBaseCombatWeapon*>())
				| std::ranges::views::filter(std::identity());
		}

		/**
		 * @brief Gets the team of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The team index.
		 */
		inline int GetTeam(CBaseEntity* entity) {
			return sm::GetEntProp<int>(entity, sm::Prop_Data, "m_iTeamNum");
		}

		/**
		 * @brief Sets the team of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iValue            The team index.
		 */
		inline void SetTeam(CBaseEntity* entity, CSTeam_e iValue)
		{
			// Validate team
			if (iValue <= CS_TEAM_SPECTATOR) /// Fix, thanks to inklesspen!
			{
				// Sets team of the entity
				sm::sourcemod::ChangeClientTeam(sm::ent_cast<IGamePlayer*>(entity), iValue);
			}
			else
			{
				// Switch team of the entity
				sm::cstrike::CS_SwitchTeam(sm::ent_cast<CBasePlayer*>(entity), iValue);
			}
		}
		/**
		 * @brief Gets the score of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The score of the entity.
		 */
		inline int GetFrags(CBaseEntity* entity) {
			return sm::GetEntProp<int>(entity, sm::Prop_Data, "m_iFrags");
		}

		/**
		 * @brief Sets the score of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @param val               The value of the score.
		 */
		inline void SetFrags(CBaseEntity* entity, int value)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Data, "m_iFrags", value);
		}

		/**
		 * @brief Gets the death of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The death of the entity.
		 */
		inline int GetDeaths(CBaseEntity* entity)
		{
			return sm::GetEntProp<int>(entity, sm::Prop_Data, "m_iDeaths");
		}

		/**
		 * @brief Sets the death of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @param val               The value of the death.
		 */
		inline void SetDeaths(CBaseEntity* entity, int value)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Data, "m_iDeaths", value);
		}

		/**
		 * @brief Gets a entity score or deaths.
		 *
		 * @param entity            The entity ptr.
		 * @param bScore            True to look at score, false to look at deaths.
		 * @return                  The score or death count of the entity.
		 */
		inline int GetScore(CBaseEntity* entity, bool score = true) { 
			return (score) ? GetFrags(entity) : GetDeaths(entity); 
		}

		/**
		 * @brief Sets a entity score or deaths.
		 *
		 * @param entity            The entity ptr.
		 * @param bScore            True to look at score, false to look at deaths.
		 * @param iValue            The score/death amount.
		 */
		inline void SetScore(CBaseEntity* entity, bool score, int val) {
			score ? SetFrags(entity, val) : SetDeaths(entity, val);
		}

		/**
		 * @brief Gets defuser value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The aspect of the entity defuser.
		 */
		inline bool GetDefuser(CBaseEntity* entity)
		{
			return sm::GetEntProp<bool>(entity, sm::Prop_Send, "m_bHasDefuser");
		}

		/**
		 * @brief Controls defuser value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of defuser.
		 */
		inline void SetDefuser(CBaseEntity* entity, bool bEnable)
		{
			sm::SetEntProp<bool>(entity, sm::Prop_Send, "m_bHasDefuser", bEnable);
		}

		/**
		 * @brief Gets the health of a entity.
		 *
		 * @param entity            The entity pointer.
		 * @param bMax              True to get maximum value, false to get health.
		 * @return                  The health value.
		 */
		inline int GetHealth(CBaseEntity* entity, bool bMax = false)
		{
			return sm::GetEntProp<int>(entity, sm::Prop_Data, bMax ? "m_iMaxHealth" : "m_iHealth");
		}

		/**
		 * @brief Sets the health of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iValue            The health value.
		 * @param bSet              True to set maximum value, false to modify health.
		 */
		inline void SetHealth(CBaseEntity* entity, int iValue, bool bSet = false)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Send, "m_iHealth", iValue);
			if (bSet) sm::SetEntProp<int>(entity, sm::Prop_Data, "m_iMaxHealth", iValue);
		}

		/**
		 * @brief Gets the speed of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The LMV value.
		 */
		inline int GetArmor(CBaseEntity* entity)
		{
			return sm::GetEntProp<int>(entity, sm::Prop_Send, "m_ArmorValue");
		}

		/**
		 * @brief Sets the armor of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iValue            The armor value.
		 */
		inline void SetArmor(CBaseEntity* entity, int iValue)
		{
			sm::SetEntProp<int>(entity, sm::Prop_Send, "m_ArmorValue", iValue);
		}

		/**
		 * @brief Gets the speed of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The LMV value.
		 */
		inline float GetLMV(CBaseEntity* entity)
		{
			return sm::GetEntProp<float>(entity, sm::Prop_Send, "m_flLaggedMovementValue");
		}

		/**
		 * @brief Sets the speed of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param flValue           The LMV value.
		 */
		inline void SetLMV(CBaseEntity* entity, float flValue)
		{
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flLaggedMovementValue", flValue);
		}

		/**
		 * @brief Gets the gravity of a entity.
		 *
		 * @param entity            The entity ptr..
		 * @return                  The gravity amount.
		 */
		inline float GetGravity(CBaseEntity* entity)
		{
			return sm::GetEntProp<float>(entity, sm::Prop_Send, "m_flGravity");
		}

		/**
		 * @brief Sets the gravity of a entity.
		 *
		 * @param entity            The entity pointer.
		 * @param flValue           The gravity amount.
		 */
		inline void SetGravity(CBaseEntity* entity, float flValue)
		{
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flGravity", flValue);
		}

		/**
		 * @brief Sets the spotting of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of spotting.
		 */
		inline void SetSpot(CBaseEntity* entity, bool enable)
		{
			if (!enable)
			{
				//sm::SetEntData<float>(ent, vec::engine::Entity_SimulationTime, flGameTime + float(val), true);
				sm::SetEntData<int>(entity, vec::engine::Player_Spotted,			false,	1,				true);
				sm::SetEntData<int>(entity, vec::engine::Player_SpottedByMask,		false,	sizeof(int),	true);
				sm::SetEntData<int>(entity, vec::engine::Player_SpottedByMask + 4,	false,	sizeof(int),	true); // table
				sm::SetEntData<int>(entity, vec::engine::Player_Spotted - 4,		0,		sizeof(int),	true);
			}
			else
			{
				sm::SetEntData<int>(entity, vec::engine::Player_Spotted - 4,		9,		sizeof(int), true);
			}
		}

		/**
		 * @brief Gets helmet value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The aspect of the entity helmet.
		 */
		inline bool GetHelmet(CBaseEntity* entity)
		{
			return sm::GetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHelmet");
		}

		/**
		 * @brief Controls helmet value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of helmet.
		 */
		inline void SetHelmet(CBaseEntity* entity, bool bEnable)
		{
			sm::SetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHelmet", bEnable);
		}

		/**
		 * @brief Gets suit value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The aspect of the entity suit.
		 */
		inline bool GetHeavySuit(CBaseEntity* entity)
		{
			return sm::GetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHeavyArmor");
		}

		/**
		 * @brief Controls suit value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of suit.
		 */
		inline void SetHeavySuit(CBaseEntity* entity, bool bEnable) {
			sm::SetEntProp<bool>(entity, sm::Prop_Send, "m_bHasHeavyArmor", bEnable);
		}

		/**
		 * @brief Gets nightvision values on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param ownership         If true, function will return the value of the entity ownership of nightvision.
		 *                          If false, function will return the value of the entity on/off state of the nightvision.
		 * @return                  True if aspect of nightvision is enabled on the entity, false if not.
		 */
		inline bool GetNightVision(CBaseEntity* pEntity, bool ownership = false) {
			return sm::GetEntProp<bool>(pEntity, sm::Prop_Send, ownership ? "m_bHasNightVision" : "m_bNightVisionOn");
		}

		/**
		 * @brief Controls nightvision values on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of nightvision. (see ownership parameter)
		 * @param bOwnership        If true, enable will toggle the entity ownership of nightvision.
		 *                          If false, enable will toggle the entity on/off state of the nightvision.
		 */
		inline void SetNightVision(CBaseEntity* pEntity, bool enable, bool ownership = false) {
			sm::SetEntProp<bool>(pEntity, sm::Prop_Send, ownership ? "m_bHasNightVision" : "m_bNightVisionOn", enable);
		}

		/**
		 * @brief Gets the addon bits of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The addon bits.
		 */
		inline int GetAddonBits(CBaseEntity* pEntity) {
			return sm::GetEntProp<int>(pEntity, sm::Prop_Send, "m_iAddonBits");
		}

		/**
		 * @brief Sets the addon bits index of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iValue            The addon bits.
		 */
		inline void SetAddonBits(CBaseEntity* pEntity, int val) {
			sm::SetEntProp<int>(pEntity, sm::Prop_Send, "m_iAddonBits", val);
		}

		/**
		 * @brief Gets the observer mode of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The mode index.
		 */
		inline int GetObserverMode(CBaseEntity* pEntity) {
			return sm::GetEntProp<int>(pEntity, sm::Prop_Data, "m_iObserverMode");
		}

		/**
		 * @brief Gets the observer target of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The target ptr.
		 */
		inline CBaseEntity* GetObserverTarget(CBaseEntity* entity) {
			return sm::GetEntPropEnt<CBaseEntity*>(entity, sm::Prop_Send, "m_hObserverTarget");
			//return sm::ent_cast<CBaseEntity*>(sm::GetEntProp<CBaseHandle>(entity, sm::Prop_Send, "m_hObserverTarget"));
		}

		/**
		 * @brief Gets hitgroup value on a entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The hitgroup index.
		 */
		inline int GetHitGroup(CBaseEntity* pEntity) {
			return sm::GetEntProp<int>(pEntity, sm::Prop_Send, "m_LastHitGroup");
		}

		/**
		 * @brief Sets the detecting of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of detection.
		 */
		inline void SetDetecting(CBaseEntity* pEntity, bool enable) {
			sm::SetEntProp<float>(pEntity, sm::Prop_Send, "m_flDetectedByEnemySensorTime", enable ? (sm::GetGameTime() + 9999.f) : 0.f);
		}

		/**
		 * @brief Sets the hud of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param pos               The hud part.
		 * @param bEnable           Enable or disable an aspect of hud.
		 */
		inline void SetHud(CBasePlayer* player, HideHUDElementFlags_t pos, bool enable) {
			// Sets hud type on the entity
			sm::SetEntProp<int>(player, sm::Prop_Send, "m_iHideHud", enable ? (sm::GetEntProp<int>(player, sm::Prop_Send, "m_iHideHud") & ~pos) : (sm::GetEntProp<int>(player, sm::Prop_Send, "m_iHideHud") | pos));
		}

		[[deprecated("Doesn't work correctly, DO NOT USE")]]
		inline const char* GetArm(CBasePlayer* entity)
		{
			return nullptr;
		}

		/**
		 * @brief Sets the arms of a entity.
		 *
		 * @param entity            The entity index.
		 * @param sModel            The model path.
		 */
		inline void SetArm(CBasePlayer* entity, char* path)
		{
			sm::SetEntProp<char*>(entity, sm::Prop_Send, "m_szArmsModel", path);
		}

		/**
		 * @brief Sets the attack delay of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param flValue           The speed amount.
		 */
		inline void SetAttack(CBaseEntity* entity, float val) {
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flNextAttack", val);
		}

		/**
		 * @brief Sets the fov of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iValue            (Optional) The fov amount.
		 */
		inline void SetFov(CBaseEntity* pEntity, int val = 90) {
			sm::SetEntProp<int>(pEntity, sm::Prop_Send, "m_iFOV", val);
			sm::SetEntProp<int>(pEntity, sm::Prop_Send, "m_iDefaultFOV", val);
		}

		/**
		 * @brief Sets body/skin for the entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iBody             (Optional) The body index.
		 * @param iSkin             (Optional) The skin index.
		 */
		inline void SetTextures(CBaseEntity* ent, int body = -1, int skin = -1) {
			if (body != -1) sm::SetEntProp<int>(ent, sm::Prop_Send, "m_nBody", body);
			if (skin != -1) sm::SetEntProp<int>(ent, sm::Prop_Send, "m_nSkin", skin);
		}

		/**
		 * @brief Gets the effect of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The effect value.
		 */
		inline int GetEffect(CBaseEntity* ent) {
			return sm::GetEntProp<int>(ent, sm::Prop_Send, "m_fEffects");
		}

		/**
		 * @brief Sets the effect of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iValue            The effect value.
		 */
		inline void SetEffect(CBaseEntity* ent, int val) {
			sm::SetEntProp<int>(ent, sm::Prop_Send, "m_fEffects", val);
		}

		/**
		 * @brief Sets the flashlight of a entity.
		 *
		 * @param entity            The entity ptr.
		 * @param bEnable           Enable or disable an aspect of flashlight.
		 */
		inline void SetFlashLight(CBaseEntity* ent, bool enable) {
			SetEffect(ent, enable ? (GetEffect(ent) ^ EF_DIMLIGHT) : 0);
		}

		/**
		 * @brief Gets the activator of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The activator ptr.
		 */
		inline CBasePlayer* GetActivator(CBaseEntity* pEntity) {
			return sm::GetEntPropEnt<CBasePlayer*>(pEntity, sm::Prop_Data, "m_pActivator");
		}

		/**
		 * @brief Sets the model of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @param iModel            The model index.
		 *							NOTE: using index here, be careful.
		 */
		inline void SetModelIndex(CBaseEntity* ent, int mdl) {
			sm::SetEntProp<int>(ent, sm::Prop_Send, "m_nModelIndex", mdl);
		}
		/**
		 * @brief Gets the owner of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The owner ptr.
		 */
		inline CBaseEntity* GetOwner(CBaseEntity* ent) {
			return sm::ent_cast<CBaseEntity*>(sm::GetEntPropEnt(ent, sm::Prop_Data, "m_hOwnerEntity"));
		}

		/**
		 * @brief Sets the owner of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @param owner             The owner ptr.
		 */
		inline void SetOwner(CBaseEntity* ent, CBaseEntity* owner) {
			sm::SetEntPropEnt<CBaseEntity*>(ent, sm::Prop_Data, "m_hOwnerEntity", owner);
		}

		/**
		 * @brief Gets the parent of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @return                  The parent ptr.
		 */
		inline CBaseEntity* GetParent(CBaseEntity* ent) {
			return sm::GetEntPropEnt<CBaseEntity*>(ent, sm::Prop_Data, "m_pParent");
		}

		/**
		 * @brief Sets the parent of an entity.
		 *
		 * @param entity            The entity ptr.
		 * @param parent            The parent ptr.
		 */
		inline void SetParent(CBaseEntity* ent, CBaseEntity* parent) {
			sm::SetEntPropEnt(ent, sm::Prop_Data, "m_pParent", parent);
		}

		/**
		 * @brief Gets the ragdoll index on a client.
		 *
		 * @param client            The client ptr.
		 * @return                  The ragdoll index.
		 */
		inline int GetRagdollIndex(CBaseEntity* pEntity) {
			return sm::GetEntPropEnt<int>(pEntity, sm::Prop_Send, "m_hRagdoll");
		}

		/**
		 * @brief Gets the collision group on a client.
		 *
		 * @param client            The client ptr.
		 * @return                  The collision group on the client.
		 */
		inline int GetCollisionGroup(CBaseEntity* ent) {
			return sm::GetEntProp<int>(ent, sm::Prop_Data, "m_CollisionGroup");
		}

		/**
		 * @brief Sets the collision group on a client.
		 *
		 * @param client            The client ptr.
		 * @param collisionGroup    The group flag.
		 */
		inline void SetCollisionGroup(CBaseEntity* ent, int val) {
			sm::SetEntProp<int>(ent, sm::Prop_Data, "m_CollisionGroup", val);
		}
		/**
		 * @brief Sets the progress bar time of a client.
		 *
		 * @param entity            The entity pointer.
		 * @param duration          The duration of the time.
		 */
		inline void SetProgressBarTime(CBasePlayer* ent, int val)
		{
			// gets the current time
			float flGameTime = sm::GetGameTime();

			// Sets the bar for the client
			sm::SetEntData(ent, vec::engine::Player_ProgressBarDuration, val, 4, true);
			sm::SetEntData<float>(ent, vec::engine::Player_ProgressBarStartTime, flGameTime, true);
			sm::SetEntData<float>(ent, vec::engine::Entity_SimulationTime, flGameTime + float(val), true);

			// Progress bar type 0-15
			sm::SetEntData(ent, vec::engine::Player_BlockingUseActionInProgress, 0, 4, true);
		}

		/**
		 * @brief Reset the progress bar.
		 *
		 * @param entity            The entity pointer.
		 */
		inline void ResetProgressBarTime(CBasePlayer* ent)
		{
			sm::SetEntData<float>(ent, vec::engine::Player_ProgressBarStartTime, 0.f, true);
			sm::SetEntData(ent, vec::engine::Player_ProgressBarDuration, 0, 1, true);
		}

		inline Vector GetMaxs(CBaseEntity* entity)
		{
			Vector Ret;
			if (sm::ent_cast<int>(entity) <= sm::GetMaxClients()) Ret = sm::GetClientMaxs(entity);
			else
				Ret = sm::GetEntProp<Vector>(entity, sm::Prop_Data, "m_vecMaxs");
			//Ret.z /= 2.f;
			return Ret;
		}

		inline Vector GetMins(CBaseEntity* entity)
		{
			Vector Ret;
			if (sm::ent_cast<int>(entity) <= sm::GetMaxClients()) Ret = sm::GetClientMins(entity);
			else
				Ret = sm::GetEntProp<Vector>(entity, sm::Prop_Data, "m_vecMins");
			//Ret.z /= 2.f;
			return Ret;
		}
		inline const char* GetModelName(CBaseEntity* entity)
		{
			return sm::GetEntProp<const char*>(entity, sm::Prop_Data, "m_ModelName");
		}
	}
}

#endif // !_VEC_STD_TOOLS_H_