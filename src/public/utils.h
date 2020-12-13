#pragma once
#ifndef _VEC_STD_UTILS_H_
#define _VEC_STD_UTILS_H_
#include "extension.h"
#include "const.h"
namespace vec
{
	namespace utils
	{
		sp_nativeinfo_t g_UTILNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);

		namespace API 
		{
			static cell_t CreateTrain(IPluginContext* pContext, const cell_t* params);
			static cell_t CreatePath(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateMonster(IPluginContext* pContext, const cell_t* params);
			static cell_t CreatePhysics(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateDynamic(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateProjectile(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateSmoke(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateParticle(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateExplosion(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateDamage(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateSprite(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateSpriteController(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateTesla(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateShooter(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateBeam(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateLight(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateGlowing(IPluginContext* pContext, const cell_t* params);
			static cell_t SetRenderColor(IPluginContext* pContext, const cell_t* params);
			static cell_t GetRenderColor(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateTracer(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateShakeScreen(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateFadeScreen(IPluginContext* pContext, const cell_t* params);
			static cell_t CreatePhysForce(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateClientHint(IPluginContext* pContext, const cell_t* params);
			static cell_t CreateClientHud(IPluginContext* pContext, const cell_t* params);
			static cell_t PrecacheModel(IPluginContext* pContext, const cell_t* params);
			static cell_t IgniteEntity(IPluginContext* pContext, const cell_t* params);
			static cell_t ExtinguishEntity(IPluginContext* pContext, const cell_t* params);
			static cell_t RemoveEntity(IPluginContext* pContext, const cell_t* params);
			static cell_t PrecacheDecal(IPluginContext* pContext, const cell_t* params);
			static cell_t PrecacheSound(IPluginContext* pContext, const cell_t* params);
			static cell_t FindHullIntersection(IPluginContext* pContext, const cell_t* params);
			static cell_t GetVelocityByAim(IPluginContext* pContext, const cell_t* params);
			static cell_t IsOnSamePlane(IPluginContext* pContext, const cell_t* params);
			static cell_t GetTraceEndPoint(IPluginContext* pContext, const cell_t* params);
			static cell_t TraceRay(IPluginContext* pContext, const cell_t* params);
			static cell_t GetDistanceBetween(IPluginContext* pContext, const cell_t* params);
			static cell_t GetEffectIndex(IPluginContext* pContext, const cell_t* params);
			static cell_t GetParticleEffectIndex(IPluginContext* pContext, const cell_t* params);
			static cell_t PrecacheParticleFile(IPluginContext* pContext, const cell_t* params);
			static cell_t PrecacheParticleEffect(IPluginContext* pContext, const cell_t* params);
			static cell_t GetEffectName(IPluginContext* pContext, const cell_t* params);
			static cell_t GetParticleEffectName(IPluginContext* pContext, const cell_t* params);
			static cell_t GetEffectNameCount(IPluginContext* pContext, const cell_t* params);
			static cell_t GetParticleEffectCount(IPluginContext* pContext, const cell_t* params);
		}

		inline CBaseEntity* CreateTrain(std::string classname, Vector position, Vector angle, std::string path, float speed, std::string sound, int flags);
		inline CBaseEntity* CreatePath(std::string classname, Vector position, Vector angle, std::string NextTarget, int flag);
		inline CBaseEntity* CreateMonster(std::string classname, Vector position, Vector angle, std::string sModel, int iFlags);
		inline CBaseEntity* CreatePhysics(std::string classname, Vector position, Vector angle, std::string model, int flags);
		inline CBaseEntity* CreateDynamic(std::string classname, Vector position, Vector angle, std::string model, std::string defaultAnim, bool bOverride, bool bHoldAnim, bool bSolid, int iFlags);
		inline CBaseEntity* CreateProjectile(Vector pos, Vector ang, std::string model);
		inline CBaseEntity* CreateSmoke(CBaseEntity* parent, Vector pos, Vector ang, std::string attach, int spradbase, int spradspeed, int speed, int startsize, int endsize, int density, int length, int twist, Color color, int transparency, std::string spritename, float removetime, float durationtime);
		inline CBaseEntity* CreateParticle(CBaseEntity* parent, Vector pos, Vector ang, std::string attach, std::string effectName, float duration);
		inline CBaseEntity* CreateExplosion(Vector vPosition, int iFlags, std::string sSpriteName, float flDamage, float flRadius, std::string sWeapon, CBaseEntity* attacker, CBaseEntity* inflictor, std::string sIgnore);
		inline CBaseEntity* CreateDamage(
			CBaseEntity* parent,	Vector pos,		CBaseEntity* attacker,	float flDamage,
			float flRadius,			int iBits,		int weaponID,			std::string sAttach);
		inline CBaseEntity* CreateSprite(
			CBaseEntity* parent, Vector pos,	Vector ang,		std::string sAttach, 
			std::string sSprite, float scale,	int rendermode, float flDurationTime);
		inline CBaseEntity* CreateSpriteController(CBaseEntity* parent, std::string sprite, std::string var);
		inline CBaseEntity* CreateTesla(
			CBaseEntity* parent, Vector pos, Vector ang, std::string attach, float radius,
			std::string sSound, int countMin, int countMax, std::string sTextureName, Color color,
			float ThickMin, float ThickMax, float LifeMin, float LifeMax, float flIntervalMin,
			float flIntervalMax, float flDurationTime
		);
		inline CBaseEntity* CreateShooter(
			CBaseEntity* parent, std::string sAttach, int iRender, int iSound, int iSkin,
			std::string sTextureName, Vector vAngle, Vector vGibAngle, float iGibs, float flDelay,
			float flVelocity, float flVariance, float flLife, float flDurationTime
		);
		inline CBaseEntity* CreateBeam(
			Vector vStartPosition, Vector vEndPosition, int iDamage, int iFrame, float flWidth, int iRenderFX, int iType,
			int iRate, std::string DecalName, int iScroll, float flScale, std::string TextureName, std::string sLife, std::string sStrike,
			int iFlags, float flAmplitude, int iRadius, int iRenderAMT, Color color, float flDelayTime, float flDurationTime, std::string sName
		);
		inline CBaseEntity* CreateLight(
			CBaseEntity* parent,	Vector vPosition,	std::string attach, int iInnerCone, int iCone,			int iBrightness, 
			int iPitch,				int iStyle,			int iFlags,			Color color,	float flDistance,	float flRadius, 
			float flDurationTime
		);
		inline void CreateGlowing(CBaseEntity* entity, bool enableState, int iType, int iRed, int iGreen, int iBlue, int iAlpha);
		inline void SetRenderColor(CBaseEntity* entity, RenderColorType_t color, int iRender);
		inline int GetRenderColor(CBaseEntity* entity, RenderColorType_t color);
		//inline void UTIL_CreateTracer(int parent, char[] sAttach, char[] sEffect, float vBullet[3], float flDurationTime)
		inline void CreateShakeScreen(CBasePlayer* client, float flAmplitude, float flFrequency, float flDurationTime);
		inline void CreateFadeScreen(CBasePlayer* client, float flDuration, float flHoldTime, int iFlags, Color vColor);
		inline void CreatePhysForce(CBaseEntity* entity, Vector vPosition, Vector vOrigin, float flDistance, float flForce, float flRadius);
		//inline void UTIL_CreateClientHint(int client, char[] sMessage)
		//inline void UTIL_CreateClientHud(Handle hSync, int client, float x, float y, float holdTime, int r, int g, int b, int a, int effect, float fxTime, float fadeIn, float fadeOut, char[] sMessage)
		//inline int UTIL_PrecacheModel(char[] sModel)
		//inline void UTIL_IgniteEntity(int entity, float flDurationTime)
		//inline void UTIL_ExtinguishEntity(int entity)
		inline void RemoveEntity(CBaseEntity* entity, float flDelayTime);
		//inline void UTIL_PrecacheDecal(char[] sDecal)
		//inline void UTIL_PrecacheSound(char[] sSound)
		//inline void UTIL_FindHullIntersection(Handle &hTrace, float vPosition[3], const float vMins[3], const float vMaxs[3], TraceEntityFilter filter, any data)
		inline void GetVelocityByAim(Vector vStartPosition, Vector vEndPosition, QAngle vAngle, Vector vVelocity, float flSpeedScale, bool verticalScale);
		//inline bool UTIL_IsOnSamePlane(int entity, int target, float vPosition[3], TraceEntityFilter filter)
		//inline bool UTIL_GetTraceEndPoint(int entity, float vPosition[3])
		//inline bool UTIL_TraceRay(int entity, int target, float vStartPosition[3], float vEndPosition[3], TraceEntityFilter filter)
		inline float GetDistanceBetween(CBaseEntity* entity1, CBaseEntity* entity2);
		inline int GetEffectIndex(const char* effect);
		inline int GetParticleEffectIndex(const char* sEffect);
		inline void PrecacheParticleFile(CBasePlayer* player, const char* sEffect);
		inline void PrecacheParticleEffect(const char* sEffect);
		inline std::string GetEffectName(int iIndex);
		inline std::string GetParticleEffectName(int iIndex);
		inline int GetEffectNameCount();
		inline int GetParticleEffectCount();
		//inline bool PlayersFilter(int entity, int contentsMask)
	}
}

#endif // !_VEC_STD_UTILS_H_
