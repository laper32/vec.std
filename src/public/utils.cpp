#include "utils.h"
#include "sm/sourcemod.h"
#include "sm/sdktools.h"

namespace vec
{
	namespace utils
	{
		/**
		* @brief Create a train entity.
		*
		* @param sClassname        The classname string.
		* @param vPosition         The position to the spawn.
		* @param vAngle            The angle to the spawn.
		* @param sPath             The name of the first path_track in the train's path.
		* @param sSpeed            The maximum speed that this train can move.
		* @param sSound            (Optional) The sound path.
		* @param iFlags            (Optional) The bits with some flags.
		*
		* @return                  The entity pointer.
		**/
		inline CBaseEntity* CreateTrain(
			std::string classname,	Vector position,			Vector angle,	std::string path, 
			float speed,			std::string sound = "",		int flags = -1)
		{
			CBaseEntity* pEntity = sm::sdktools::CreateEntityByName("func_tracktrain");

			if (!pEntity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(pEntity, "origin", position);
				sm::sdktools::DispatchKeyValue<Vector>(pEntity, "angles", angle);
				sm::sdktools::DispatchKeyValue<const char*>(pEntity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(pEntity, "target", path.c_str());
				sm::sdktools::DispatchKeyValue<float>(pEntity, "speed", speed);
				sm::sdktools::DispatchKeyValue<int>(pEntity, "wheels", 256); // Make moving smoother
				sm::sdktools::DispatchKeyValue<int>(pEntity, "bank", 20); // Make turning smoother
				sm::sdktools::DispatchKeyValue<int>(pEntity, "orientationtype", 2); // Linear blend, add some smoothness
				sm::sdktools::DispatchKeyValue<int>(pEntity, "spawnflags", flags); 
				if (!sound.size()) sm::sdktools::DispatchKeyValue<const char*>(pEntity, "MoveSound", sound.c_str());
				
				SetRenderColor(pEntity, RenderColorType_t::Color_Alpha, 0);

				sm::sdktools::DispatchSpawn(pEntity);

			}
			return pEntity;
		}

		inline CBaseEntity* CreatePath(std::string classname, Vector position, Vector angle, std::string NextTarget, int flag = 0)
		{
			CBaseEntity* pEntity = sm::sdktools::CreateEntityByName("path_track");

			if (!pEntity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(pEntity, "origin", position);
				sm::sdktools::DispatchKeyValue<Vector>(pEntity, "angle", angle);
				sm::sdktools::DispatchKeyValue<const char*>(pEntity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(pEntity, "target", NextTarget.c_str());
				sm::sdktools::DispatchKeyValue<int>(pEntity, "flags", flag);
				
				sm::sdktools::DispatchSpawn(pEntity);

				sm::sdktools::ActivateEntity(pEntity);
			}
			return pEntity;
		}

		inline CBaseEntity* CreateMonster(std::string classname, Vector position, Vector angle, std::string sModel, int iFlags)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("monster_generic");
			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<const char*>(entity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", position);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", angle);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "model", sModel.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", iFlags);
				
				sm::sdktools::DispatchSpawn(entity);

				sm::SetEntProp<int>(entity, sm::Prop_Data, "m_bloodColor", -1);
			}
			return entity;
		}

		inline CBaseEntity* CreatePhysics(std::string classname, Vector position, Vector angle, std::string model, int flags)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("prop_physics_multiplayer");

			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<const char*>(entity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", position);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", angle);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "model", model.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", flags);

				sm::sdktools::DispatchSpawn(entity);
			}

			return entity;
		}

		inline CBaseEntity* CreateDynamic(
			std::string classname,		Vector position,	Vector angle,	std::string model, 
			std::string defaultAnim,	bool bOverride,		bool bHoldAnim, bool bSolid, int iFlags)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName(bOverride ? "prop_dynamic_override" : "prop_dynamic");

			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<const char*>(entity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", position);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", angle);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "model", model.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", iFlags);
				sm::sdktools::DispatchKeyValue<int>(entity, "solid", bSolid ? 1 : 0);
				sm::sdktools::DispatchKeyValue<int>(entity, "HoldAnimation", bHoldAnim ? 1 : 0);
				if (!defaultAnim.size()) sm::sdktools::DispatchKeyValue(entity, "DefaultAnim", defaultAnim.c_str());

				sm::sdktools::DispatchSpawn(entity);
			}
			return entity;
		}

		inline CBaseEntity* CreateProjectile(Vector pos, Vector ang, std::string model)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("hegrenade_projectile");

			if (!entity)
			{
				sm::sdktools::DispatchSpawn(entity);

				sm::sdktools::TeleportEntity(entity, pos, ang, {});
				
				if (!model.size()) sm::sdktools::SetEntityModel(entity, model.c_str());
			}

			return entity;
		}

		inline CBaseEntity* CreateSmoke(
			CBaseEntity* parent,	Vector pos,			Vector ang,				std::string attach,		int spreadbase, int spreadspeed,
			int speed,				int startsize,		int endsize,			int density,			int length,		int twist,		
			Color color,			int transparency,	std::string spritename, float removetime,		float durationtime)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_smokestack");

			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", pos);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", ang);
				sm::sdktools::DispatchKeyValue<int>(entity, "BaseSpread", spreadbase);
				sm::sdktools::DispatchKeyValue<int>(entity, "SpreadSpeed", spreadspeed);
				sm::sdktools::DispatchKeyValue<int>(entity, "Speed", speed);
				sm::sdktools::DispatchKeyValue<int>(entity, "StartSize", startsize);
				sm::sdktools::DispatchKeyValue<int>(entity, "EndSize", endsize);
				sm::sdktools::DispatchKeyValue<int>(entity, "Rate", density);
				sm::sdktools::DispatchKeyValue<int>(entity, "JetLength", length);
				sm::sdktools::DispatchKeyValue<int>(entity, "Twist", twist);
				std::string ColorBuffer = std::string() + std::to_string(color.r()) + " " + std::to_string(color.g()) + " " + std::to_string(color.b());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "RenderColor", ColorBuffer.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "RenderAmt", transparency);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "SmokeMaterial", spritename.c_str());

				sm::sdktools::DispatchSpawn(entity);
				sm::sdktools::AcceptEntityInput(entity, "TurnOn");

				if (!parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (!attach.size())
					{
						sm::sdktools::SetVariant(attach);
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}

				if (durationtime > 0.0 && removetime > 0.0)
				{
					std::string buffer = "OnUser2 !self:TurnOff::" + std::to_string(removetime) + ":1";
					sm::sdktools::SetVariant(buffer);
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");
					sm::sdktools::AcceptEntityInput(entity, "FireUser2");
					RemoveEntity(entity, durationtime);
				}
			}

			return entity;
		}

		inline CBaseEntity* CreateParticle(CBaseEntity* parent, Vector pos, Vector ang, std::string attach, std::string effectName, float duration)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("info_particle_system");
			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", pos);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", ang);
				sm::sdktools::DispatchKeyValue<int>(entity, "start_active", 1);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "effect_name", effectName.c_str());

				sm::sdktools::DispatchSpawn(entity);

				if (!parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (!attach.size())
					{
						sm::sdktools::SetVariant(attach);
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}
				sm::sdktools::ActivateEntity(entity);
				sm::sdktools::AcceptEntityInput(entity, "Start");

				if (duration > 0.f) RemoveEntity(entity, duration);
			}
			return entity;
		}

		inline CBaseEntity* CreateExplosion(Vector vPosition, int iFlags, std::string sSpriteName, float flDamage, float flRadius, std::string sWeapon, CBaseEntity* attacker, CBaseEntity* inflictor, std::string sIgnore)
		{
			return nullptr;
		}

		inline CBaseEntity* UTIL_CreateDamage(CBaseEntity* parent, Vector pos, int attacker, float flDamage, float flRadius, int iBits, int weaponID, std::string sAttach)
		{
			return nullptr;
		}

		inline CBaseEntity* UTIL_CreateSprite(
			CBaseEntity* parent, Vector pos, Vector ang, std::string sAttach, 
			std::string sSprite, float scale, int rendermode, float flDurationTime)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_sprite");

			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", pos);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", ang);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "model", sSprite.c_str());
				sm::sdktools::DispatchKeyValue<float>(entity, "scale", scale);
				sm::sdktools::DispatchKeyValue<int>(entity, "rendermode", rendermode);

				sm::sdktools::DispatchSpawn(entity);

				sm::sdktools::ActivateEntity(entity);

				if (!parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (sAttach.size())
					{
						sm::sdktools::SetVariant(sAttach);
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}

				if (flDurationTime > 0.f) RemoveEntity(entity, flDurationTime);
			}
			return entity;
		}
		inline CBaseEntity* UTIL_CreateSpriteController(CBaseEntity* parent, std::string sprite, std::string var)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("material_modify_control");

			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<const char*>(entity, "materialName", sprite.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "materialVar", var.c_str());

				sm::sdktools::DispatchSpawn(entity);

				if (!parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);
				}
			}

			return entity;
		}
		inline CBaseEntity* UTIL_CreateTesla(
			CBaseEntity* parent, Vector pos, Vector ang, std::string attach = "", float radius = 500.0, 
			std::string sSound = "DoSpark", int countMin = 42, int countMax = 62, std::string sTextureName = "materials/sprites/physbeam.vmt", 
			Color color = {255, 255, 255}, float ThickMin = 10.0, float ThinkMax = 11.0, float LifeMin = 0.3, 
			float LifeMax = 0.3, float sIntervalMin = 0.1, float sIntervalMax = 0.2, float flDurationTime = 0.0)
		{
			return nullptr;
		}
		inline CBaseEntity* UTIL_CreateShooter(
		CBaseEntity* parent, std::string sAttach, int iRender, int iSound, int iSkin, 
		std::string sTextureName, Vector vAngle, Vector vGibAngle, float iGibs, 
		float flDelay, float flVelocity, float flVariance, float flLife, float flDurationTime)
		{

		}
		inline CBaseEntity* CreateBeam(
			Vector vStartPosition, Vector vEndPosition, int iDamage, int iFrame, float flWidth, int iRenderFX, int iType,
			int iRate, std::string DecalName, int iScroll, float flScale, std::string TextureName, std::string sLife, std::string sStrike,
			int iFlags, float flAmplitude, int iRadius, int iRenderAMT, Color color, float flDelayTime, float flDurationTime, std::string sName
		)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_beam");
			if (!entity)
			{
				std::string classNameBuffer = sName + std::to_string(sm::ent_cast<int>(entity));

				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", vStartPosition);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "targetname", classNameBuffer.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "damage", iDamage);
				sm::sdktools::DispatchKeyValue<int>(entity, "framestart", iFrame);
				sm::sdktools::DispatchKeyValue<float>(entity, "BoltWidth", flWidth);
				sm::sdktools::DispatchKeyValue<int>(entity, "renderfx", iRenderFX);
				sm::sdktools::DispatchKeyValue<int>(entity, "TouchType", iType);
				sm::sdktools::DispatchKeyValue<int>(entity, "framerate", iRate);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "decalname", DecalName.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "TextureScroll", iScroll);
				sm::sdktools::DispatchKeyValue<float>(entity, "HDRColorScale", flScale);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "texture", TextureName.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "life", sLife.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "StrikeTime", sStrike.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "LightningStart", classNameBuffer.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", iFlags);
				sm::sdktools::DispatchKeyValue<float>(entity, "NoiseAmplitude", flAmplitude);
				sm::sdktools::DispatchKeyValue<int>(entity, "Radius", iRadius);
				sm::sdktools::DispatchKeyValue<int>(entity, "renderamt", iRenderAMT);
				std::string ColorBuffer = std::string() + std::to_string(color.r()) + " " + std::to_string(color.g()) + " " + std::to_string(color.b());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "rendercolor", ColorBuffer.c_str());
				
				sm::sdktools::DispatchSpawn(entity);
				
				sm::sdktools::AcceptEntityInput(entity, "TurnOff");
				sm::sdktools::AcceptEntityInput(entity, "TurnOn");
				
				sm::sdktools::SetEntityModel(entity, TextureName.c_str());
				
				sm::SetEntProp<float>(entity, sm::Prop_Data, "m_flWidth", flWidth);
				sm::SetEntProp<float>(entity, sm::Prop_Data, "m_flEndWidth", flWidth);
				sm::SetEntProp<Vector>(entity, sm::Prop_Data, "m_vecEndPos", vEndPosition);

				if (flDurationTime > 0.f) RemoveEntity(entity, flDurationTime);

				if (flDelayTime > 0.f)
				{
					std::string VariantBuffer = "OnUser2 !self:TurnOff::" + std::to_string(flDelayTime - 0.001) + ":1";

					sm::sdktools::SetVariant(VariantBuffer);
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");

					VariantBuffer = "OnUser2 !self:TurnOn::" + std::to_string(flDelayTime) + ":1";
					sm::sdktools::SetVariant(VariantBuffer);
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");
					
					// Execute touch hook tweak
					sm::sdktools::SetVariant("OnTouchedByEntity !self:FireUser2::0.0:-1");
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");
					sm::sdktools::SetVariant("OnTouchedByEntity !self:FireUser3::0.0:-1");
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");
				}
			}
			return entity;
		}
		inline CBaseEntity* CreateLight(
			CBaseEntity* parent, Vector vPosition, std::string attach, int iInnerCone, int iCone,
			int iBrightness, int iPitch, int iStyle, int iFlags, Color color, float flDistance, float flRadius, float flDurationTime
			)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("light_dynamic");

			if (!entity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", vPosition);
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", iFlags);
				sm::sdktools::DispatchKeyValue<int>(entity, "inner_cone", iInnerCone);
				sm::sdktools::DispatchKeyValue<int>(entity, "cone", iCone);
				sm::sdktools::DispatchKeyValue<int>(entity, "brightness", iBrightness);
				sm::sdktools::DispatchKeyValue<int>(entity, "pitch", iPitch);
				sm::sdktools::DispatchKeyValue<int>(entity, "style", iStyle);
				std::string ColorBuffer = std::string() + std::to_string(color.r()) + " " + std::to_string(color.g()) + " " + std::to_string(color.b());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "_light", ColorBuffer.c_str());
				sm::sdktools::DispatchKeyValue<float>(entity, "distance", flDistance);
				sm::sdktools::DispatchKeyValue<float>(entity, "spotlight_radius", flRadius);

				sm::sdktools::DispatchSpawn(entity);
				sm::sdktools::AcceptEntityInput(entity, "TurnOn");
				
				if (!parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (attach.size())
					{
						sm::sdktools::SetVariant(attach);
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}
				if (flDurationTime > 0.f) RemoveEntity(entity, flDurationTime);
			}

			return entity;
		}

		inline void UTIL_CreateGlowing(CBaseEntity* entity, bool enableState, int iType = 0, int iRed = 255, int iGreen = 255, int iBlue = 255, int iAlpha = 255)
		{
			static int iGlowOffset = 0;
			if (!iGlowOffset && (iGlowOffset = sm::GetEntSendPropOffs(entity, "m_clrGlow")) == -1) return;
			sm::SetEntProp(entity, sm::Prop_Send, "m_bShouldGlow", enableState, true);
			sm::SetEntProp(entity, sm::Prop_Send, "m_nGlowStyle", iType);
			sm::SetEntProp<float>(entity, sm::Prop_Send, "m_flGlowMaxDist", 999999.0);

			sm::SetEntData<int>(entity, iGlowOffset + 0, iRed,		{}, true);
			sm::SetEntData<int>(entity, iGlowOffset + 1, iGreen,	{}, true);
			sm::SetEntData<int>(entity, iGlowOffset + 2, iBlue,		{}, true);
			sm::SetEntData<int>(entity, iGlowOffset + 3, iAlpha,	{}, true);
		}
		inline void SetRenderColor(CBaseEntity* entity, RenderColorType_t color, int iRender)
		{
			static int renderoffset = 0;
			if (!renderoffset && (renderoffset = sm::GetEntSendPropOffs(entity, "m_clrRender")) == -1) return;

			sm::SetEntProp<int>(entity, sm::Prop_Send, "m_nRenderMode", RenderMode_t::kRenderTransAlpha);
			sm::SetEntData<int>(entity, renderoffset + static_cast<int>(color), iRender, 1, true);
		}
		inline int GetRenderColor(CBaseEntity* entity, RenderColorType_t color)
		{
			static int renderoffset = 0;
			if (!renderoffset && (renderoffset = sm::GetEntSendPropOffs(entity, "m_clrRender")) == -1) return 255;
			return sm::GetEntData<int>(entity, renderoffset + static_cast<int>(color), 1);
		}
		inline void CreateTracer(CBaseEntity* parent, std::string attach, std::string effect, Vector bullet, float duration)
		{

		}
		inline void CreateShakeScreen(CBasePlayer* client, float flAmplitude, float flFrequency, float flDurationTime)
		{
			
		}
		//inline void UTIL_CreateShakeScreen(int client, float flAmplitude, float flFrequency, float flDurationTime)
		//inline void UTIL_CreateFadeScreen(int client, float flDuration, float flHoldTime, int iFlags, int vColor[4])
		//inline void UTIL_CreatePhysForce(int client, float vPosition[3], float vOrigin[3], float flDistance, float flForce, float flRadius)
		//inline void UTIL_CreateClientHint(int client, char[] sMessage)
		//inline void UTIL_CreateClientHud(Handle hSync, int client, float x, float y, float holdTime, int r, int g, int b, int a, int effect, float fxTime, float fadeIn, float fadeOut, char[] sMessage)
		inline int UTIL_PrecacheModel(std::string sModel)
		{

		}
		inline void UTIL_IgniteEntity(CBaseEntity* entity, float flDurationTime)
		{

		}
		inline void UTIL_ExtinguishEntity(CBaseEntity* entity)
		{

		}
		inline void RemoveEntity(CBaseEntity* entity, float flDelayTime)
		{
			std::string buffer = "OnUser1 !self:Kill::" + std::to_string(flDelayTime) + ":1";
			sm::sdktools::SetVariant(buffer);
			sm::sdktools::AcceptEntityInput(entity, "AddOutput");
			sm::sdktools::AcceptEntityInput(entity, "FireUser1");
		}
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