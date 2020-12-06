#pragma once
#ifndef _VEC_STD_UTILS_H_
#define _VEC_STD_UTILS_H_
#include "extension.h"
#include "const.h"
namespace vec
{
	namespace utils
	{
		inline CBaseEntity* CreateTrain(
			std::string classname, Vector position, Vector angle, std::string path, 
			float speed, std::string sound, int flags);
		inline CBaseEntity* CreatePath(std::string classname, Vector position, Vector angle, std::string NextTarget, int flag);
		inline CBaseEntity* CreateMonster(std::string classname, Vector position, Vector angle, std::string sModel, int iFlags);
		inline CBaseEntity* CreatePhysics(std::string classname, Vector position, Vector angle, std::string model, int flags);
		inline CBaseEntity* CreateDynamic(
			std::string classname,	Vector position,	Vector angle,	std::string model, std::string defaultAnim,
			bool bOverride,			bool bHoldAnim,		bool bSolid,	int iFlags);
		inline CBaseEntity* CreateProjectile(Vector pos, Vector ang, std::string model);
		inline CBaseEntity* CreateSmoke(
			CBaseEntity* parent,	Vector pos,			Vector ang,				std::string attach, 
			int spradbase,			int spradspeed,		int speed,				int startsize,
			int endsize,			int density,		int length,				int twist, 
			Color color,			int transparency,	std::string spritename, float removetime,
			float durationtime);
		inline CBaseEntity* CreateParticle(
			CBaseEntity* parent,		Vector pos,				Vector ang, 
			std::string attach,			std::string effectName, float duration);
		inline CBaseEntity* CreateExplosion(
			Vector vPosition,			int iFlags,				std::string sSpriteName,
			float flDamage,				float flRadius,			std::string sWeapon,
			CBaseEntity* attacker,		CBaseEntity* inflictor, std::string sIgnore);
		inline CBaseEntity* UTIL_CreateDamage(
			CBaseEntity* parent, Vector pos, int attacker, float flDamage,
			float flRadius, int iBits, int weaponID, std::string sAttach);
		inline CBaseEntity* UTIL_CreateSprite(
			CBaseEntity* parent, Vector pos,	Vector ang,		std::string sAttach, 
			std::string sSprite, float scale,	int rendermode, float flDurationTime);
		//inline int UTIL_CreateSpriteController(int parent, char[] sSprite, char[] sVar)
		//inline int UTIL_CreateTesla(int parent = -1, float vPosition[3] = NULL_VECTOR, float vAngle[3] = NULL_VECTOR, char[] sAttach = "", char[] sRadius = "500.0", char[] sSound = "DoSpark", char[] sCountMin = "42", char[] sCountMax = "62", char[] sTextureName = "materials/sprites/physbeam.vmt", char[] sColor = "255 255 255", char[] sThickMin = "10.0", char[] sThickMax = "11.0", char[] sLifeMin = "0.3", char[] sLifeMax = "0.3", char[] sIntervalMin = "0.1", char[] sIntervalMax = "0.2", float flDurationTime = 0.0)
		//inline int UTIL_CreateShooter(int parent, char[] sAttach, char[] sRender = "5", char[] sSound = "-1", int iSkin = 0, char[] sTextureName, float vAngle[3] = NULL_VECTOR, float vGibAngle[3] = NULL_VECTOR, float iGibs, float flDelay, float flVelocity, float flVariance, float flLife, float flDurationTime)
		//inline int UTIL_CreateBeam(float vStartPosition[3], float vEndPosition[3], char[] sDamage = "0", char[] sFrame = "0", char[] sWidth = "4.0", char[] sRenderFX = "0", char[] sType = "3", char[] sRate = "0", char[] sDecalName = "Bigshot", char[] sScroll = "35", char[] sScale = "1.0", char[] sTextureName = "materials/sprites/purplelaser1.vmt", char[] sLife = "0", char[] sStrike = "1", int iFlags = 0, char[] sAmplitude = "0", char[] sRadius = "256", char[] sRenderAMT = "100", char[] sColor, float flDelayTime, float flDurationTime, char[] sName)
		//inline int UTIL_CreateLight(int parent = -1, float vPosition[3] = NULL_VECTOR, char[] sAttach = "", char[] sInnerCone = "0", char[] sCone = "80", char[] sBrightness = "1", char[] sPitch = "90", char[] sStyle = "1", int iFlags = 0, char[] sColor, float flDistance, float flRadius, float flDurationTime = 0.0)
		//inline void UTIL_CreateGlowing(int entity, bool enableState, int iType = 0, int iRed = 255, int iGreen = 255, int iBlue = 255, int iAlpha = 255)
		inline void SetRenderColor(CBaseEntity* entity, RenderColorType_t color, int iRender);
		inline int GetRenderColor(CBaseEntity* entity, RenderColorType_t color);
		//inline void UTIL_CreateTracer(int parent, char[] sAttach, char[] sEffect, float vBullet[3], float flDurationTime)
		//inline void UTIL_CreateShakeScreen(int client, float flAmplitude, float flFrequency, float flDurationTime)
		//inline void UTIL_CreateFadeScreen(int client, float flDuration, float flHoldTime, int iFlags, int vColor[4])
		//inline void UTIL_CreatePhysForce(int client, float vPosition[3], float vOrigin[3], float flDistance, float flForce, float flRadius)
		//inline void UTIL_CreateClientHint(int client, char[] sMessage)
		//inline void UTIL_CreateClientHud(Handle hSync, int client, float x, float y, float holdTime, int r, int g, int b, int a, int effect, float fxTime, float fadeIn, float fadeOut, char[] sMessage)
		//inline int UTIL_PrecacheModel(char[] sModel)
		//inline void UTIL_IgniteEntity(int entity, float flDurationTime)
		//inline void UTIL_ExtinguishEntity(int entity)
		inline void RemoveEntity(CBaseEntity* entity, float flDelayTime);
		//inline void UTIL_PrecacheDecal(char[] sDecal)
		//inline void UTIL_PrecacheSound(char[] sSound)
		//inline void UTIL_FindHullIntersection(Handle &hTrace, float vPosition[3], const float vMins[3], const float vMaxs[3], TraceEntityFilter filter, any data)
		//inline void UTIL_GetVelocityByAim(float vStartPosition[3], float vEndPosition[3], float vAngle[3], float vVelocity[3], float flSpeedScale = 1.0, bool verticalScale = false)
		//inline bool UTIL_IsOnSamePlane(int entity, int target, float vPosition[3], TraceEntityFilter filter)
		//inline bool UTIL_GetTraceEndPoint(int entity, float vPosition[3])
		//inline bool UTIL_TraceRay(int entity, int target, float vStartPosition[3], float vEndPosition[3], TraceEntityFilter filter)
		//inline float UTIL_GetDistanceBetween(int client, int entity)
		//inline int GetEffectIndex(char[] sEffect)
		//inline int GetParticleEffectIndex(char[] sEffect)
		//inline void PrecacheParticleFile(int client = 0, char[] sEffect)
		//inline void PrecacheParticleEffect(char[] sEffect)
		//inline void GetEffectName(int iIndex, char[] sEffect, int iMaxLen)
		//inline void GetParticleEffectName(int iIndex, char[] sEffect, int iMaxLen)
		//inline void GetEffectNameCount(/*void*/)
		//inline int GetParticleEffectCount();
		//inline bool PlayersFilter(int entity, int contentsMask)
	}
}

#endif // !_VEC_STD_UTILS_H_
