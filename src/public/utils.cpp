#include "utils.h"
#include "sm/sourcemod.h"
#include "sm/sdktools.h"
#include <cmath>

namespace vec
{
	namespace utils
	{
		sp_nativeinfo_t g_UTILNatives[] = {
			{"UTIL_CreateTrain",		API::CreateTrain},
			{"UTIL_CreatePath",			API::CreatePath},
			{"UTIL_CreateMonster",		API::CreateMonster},
			{"UTIL_CreatePhysics",		API::CreatePhysics},
			{"UTIL_CreateDynamic",		API::CreateDynamic},
			{"UTIL_CreateProjectile",	API::CreateProjectile},
			{"UTIL_CreateSmoke",		API::CreateSmoke},
			{"UTIL_CreateParticle",		API::CreateParticle},
			{"UTIL_CreateExplosion",	API::CreateExplosion},
			{"UTIL_CreateDamage",		API::CreateDamage},
			{"UTIL_CreateSprite",		API::CreateSprite},
			{"UTIL_CreateSpriteController", API::CreateSpriteController},
			{"UTIL_CreateTesla",		API::CreateTesla},
			{"UTIL_CreateShooter",		API::CreateShooter},
			{"UTIL_CreateBeam",			API::CreateBeam},
			{"UTIL_CreateLight",		API::CreateLight},
			{"UTIL_CreateGlowing",		API::CreateGlowing},
			{"UTIL_SetRenderColor",		API::SetRenderColor},
			{"UTIL_GetRenderColor",		API::GetRenderColor},
			{"UTIL_CreateTracer",		API::CreateTracer},
			{"UTIL_CreateShakeScreen",	API::CreateShakeScreen},
			{"UTIL_CreateFadeScreen",	API::CreateFadeScreen},
			{"UTIL_CreatePhysForce",	API::CreatePhysForce},
			{"UTIL_CreateClientHint",	API::CreateClientHint},
			{"UTIL_CreateClientHud",	API::CreateClientHud},
			{"UTIL_PrecacheModel",		API::PrecacheModel},
			{"UTIL_IgniteEntity",		API::IgniteEntity},
			{"UTIL_ExtinguishEntity",	API::ExtinguishEntity},
			{"UTIL_RemoveEntity",		API::RemoveEntity},
			//{"UTIL_PrecacheDecal",		API::PrecacheDecal},
			//{"UTIL_PrecacheSound",		API::PrecacheSound},
			//{"UTIL_FindHullIntersection", API::FindHullIntersection},
			//{"UTIL_GetVelocityByAim",		API::GetVelocityByAim},
			//UTIL_IsOnSamePlane
			//UTIL_GetTraceEndPoint
			//UTIL_TraceRay
			//UTIL_GetDistanceBetween
			//GetEffectIndex
			//GetParticleEffectIndex
			//PrecacheParticleFile
			//PrecacheParticleEffect
			//GetEffectName
			//GetParticleEffectName
			//GetEffectNameCount
			//GetParticleEffectCount
			{nullptr, nullptr}
		};

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_UTILNatives);
			return true;
		}

		namespace API
		{
			static cell_t CreateTrain(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreatePath(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateMonster(IPluginContext* pContext, const cell_t* params)
			{

				return 0;
			}

			static cell_t CreatePhysics(IPluginContext* pContext, const cell_t* params)
			{

				return 0;
			}

			static cell_t CreateDynamic(IPluginContext* pContext, const cell_t* params)
			{

				return 0;
			}

			static cell_t CreateProjectile(IPluginContext* pContext, const cell_t* params)
			{

				return 0;
			}

			static cell_t CreateSmoke(IPluginContext* pContext, const cell_t* params)
			{

				return 0;
			}

			static cell_t CreateParticle(IPluginContext* pContext, const cell_t* params)
			{
				CBaseEntity* parent = sm::ent_cast<CBaseEntity*>(params[1]);
				Vector pos, ang;
				sm::interop::cell2native(pContext, params[2], pos);
				sm::interop::cell2native(pContext, params[3], ang);
				std::string attach, effectName;
				sm::interop::cell2native(pContext, params[4], attach);
				sm::interop::cell2native(pContext, params[5], effectName);
				float flDuration = sp_ctof(params[6]);
				CBaseEntity* Ret = vec::utils::CreateParticle(parent, pos, ang, attach, effectName, flDuration);
				return sm::ent_cast<cell_t>(Ret);
			}

			static cell_t CreateExplosion(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateDamage(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateSprite(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateSpriteController(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateTesla(IPluginContext* pContext, const cell_t* params)
			{
				return 0;

			}

			static cell_t CreateShooter(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateBeam(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateLight(IPluginContext* pContext, const cell_t* params)
			{
				CBaseEntity* parent = sm::ent_cast<CBaseEntity*>(params[1]);
				Vector pos;
				sm::interop::cell2native(pContext, params[2], pos);
				std::string attach;
				sm::interop::cell2native(pContext, params[3], attach);
				Color clr;
				sm::interop::cell2native(pContext, params[10], clr);
				CBaseEntity* Ret = vec::utils::CreateLight(parent, pos, attach, params[4], params[5], params[6], params[7],
					params[8], params[9], clr, sp_ftoc(params[11]), sp_ftoc(params[12]), sp_ftoc(params[13]));

				return sm::ent_cast<cell_t>(Ret);
			}
			static cell_t CreateGlowing(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t SetRenderColor(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetRenderColor(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateTracer(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateShakeScreen(IPluginContext* pContext, const cell_t* params)
			{

				return 0;
			}

			static cell_t CreateFadeScreen(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreatePhysForce(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t CreateClientHint(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}
			
			[[deprecated]]
			static cell_t CreateClientHud(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t PrecacheModel(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t IgniteEntity(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t ExtinguishEntity(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t RemoveEntity(IPluginContext* pContext, const cell_t* params)
			{
				vec::utils::RemoveEntity(sm::ent_cast<CBaseEntity*>(params[1]), sp_ctof(params[2]));
				return 1;
			}
			
			static cell_t PrecacheDecal(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t PrecacheSound(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t FindHullIntersection(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetVelocityByAim(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t IsOnSamePlane(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetTraceEndPoint(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t TraceRay(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetDistanceBetween(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetEffectIndex(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetParticleEffectIndex(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t PrecacheParticleFile(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t PrecacheParticleEffect(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetEffectName(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetParticleEffectName(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetEffectNameCount(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

			static cell_t GetParticleEffectCount(IPluginContext* pContext, const cell_t* params)
			{
				return 0;
			}

		}

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

			if (pEntity)
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
				if (sound.size()) sm::sdktools::DispatchKeyValue<const char*>(pEntity, "MoveSound", sound.c_str());
				
				SetRenderColor(pEntity, RenderColorType_t::Color_Alpha, 0);

				sm::sdktools::DispatchSpawn(pEntity);

			}
			return pEntity;
		}

		/**
		 * @brief Create a path entity.
		 *
		 * @param sClassname        The classname string.
		 * @param vPosition         The position to the spawn.
		 * @param vAngle            The angle to the spawn.
		 * @param sNextTarget       The next '_track' in the path.
		 * @param iFlags            (Optional) The bits with some flags.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreatePath(std::string classname, Vector position, Vector angle, std::string NextTarget, int flag = 0)
		{
			CBaseEntity* pEntity = sm::sdktools::CreateEntityByName("path_track");

			if (pEntity)
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

		/**
		 * @brief Create a monster entity.
		 *
		 * @param sClassname        The classname string.
		 * @param vPosition         The position to the spawn.
		 * @param vAngle            The angle to the spawn.
		 * @param sModel            The model path.
		 * @param iFlags            (Optional) The bits with some flags.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateMonster(std::string classname, Vector position, Vector angle, std::string sModel, int iFlags)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("monster_generic");
			if (entity)
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

		/**
		 * @brief Create a physics entity.
		 *
		 * @param sClassname        The classname string.
		 * @param vPosition         The position to the spawn.
		 * @param vAngle            The angle to the spawn.
		 * @param sModel            The model path.
		 * @param iFlags            (Optional) The bits with some flags.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreatePhysics(std::string classname, Vector position, Vector angle, std::string model, int flags)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("prop_physics_multiplayer");

			if (entity)
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

		/**
		 * @brief Create a dynamic entity.
		 *
		 * @param sClassname        The classname string.
		 * @param vPosition         The position to the spawn.
		 * @param vAngle            The angle to the spawn.
		 * @param sModel            The model path.
		 * @param sDefaultAnim      (Optional) The default animation.
		 * @param bOverride         (Optional) True for models with physics, false for fully dynamic models.
		 * @param bHoldAnim         (Optional) If set, the prop will not loop its animation, but hold the last frame.
		 * @param bSolid            (Optional) If set, the prop will be solid.
		 * @param iFlags            (Optional) The bits with some flags.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateDynamic(
			std::string classname,		Vector position,	Vector angle,	std::string model, 
			std::string defaultAnim,	bool bOverride,		bool bHoldAnim, bool bSolid, int iFlags)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName(bOverride ? "prop_dynamic_override" : "prop_dynamic");

			if (entity)
			{
				sm::sdktools::DispatchKeyValue<const char*>(entity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", position);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", angle);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "model", model.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", iFlags);
				sm::sdktools::DispatchKeyValue<int>(entity, "solid", bSolid ? 1 : 0);
				sm::sdktools::DispatchKeyValue<int>(entity, "HoldAnimation", bHoldAnim ? 1 : 0);
				if (defaultAnim.size()) sm::sdktools::DispatchKeyValue(entity, "DefaultAnim", defaultAnim.c_str());

				sm::sdktools::DispatchSpawn(entity);
			}
			return entity;
		}

		/**
		 * @brief Create a projectile entity.
		 *
		 * @param vPosition         The position to the spawn.
		 * @param vAngle            The angle to the spawn.
		 * @param sModel            (Optional) The model path.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateProjectile(Vector pos, Vector ang, std::string model)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("hegrenade_projectile");

			if (entity)
			{
				sm::sdktools::DispatchSpawn(entity);

				sm::sdktools::TeleportEntity(entity, pos, ang, {});
				
				if (model.size()) sm::sdktools::SetEntityModel(entity, model.c_str());
			}

			return entity;
		}

		/**
		 * @brief Create a stack of the smoke entity.
		 *
		 * @param parent            (Optional) The parent index.
		 * @param vPosition         (Optional) The position to the spawn.
		 * @param vAngle            (Optional) The angle to the spawn.
		 * @param sAttach           (Optional) The attachment name.
		 * @param sSpreadBase       (Optional) The amount of random spread in the origins of the smoke particles when they're spawned.
		 * @param sSpreadSpeed      (Optional) The amount of random spread in the velocity of the smoke particles after they're spawned.
		 * @param sSpeed            (Optional) The speed at which the smoke particles move after they're spawned.
		 * @param sStartSize        (Optional) The size of the smoke particles when they're first emitted.
		 * @param sEndSize          (Optional) The size of the smoke particles at the point they fade out completely.
		 * @param sDensity          (Optional) The rate at which to emit smoke particles (i.e. particles to emit per second).
		 * @param sLength           (Optional) The length of the smokestack. Lifetime of the smoke particles is derived from this & particle speed.
		 * @param sTwist            (Optional) The amount, in degrees per second, that the smoke particles twist around the origin.
		 * @param sColor            The color of the light. (RGB)
		 * @param sTransparency     The amount of an alpha (0-255)
		 * @param sSpriteName       The sprite path.
		 * @param flRemoveTime      (Optional) The removing of the smoke.
		 * @param flDurationTime    (Optional) The duration of the smoke.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateSmoke(
			CBaseEntity* parent,	Vector pos,			Vector ang,				std::string attach,		int spreadbase, int spreadspeed,
			int speed,				int startsize,		int endsize,			int density,			int length,		int twist,		
			Color color,			int transparency,	std::string spritename, float removetime,		float durationtime)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_smokestack");

			if (entity)
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

				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (attach.size())
					{
						sm::sdktools::SetVariant(attach.c_str());
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}

				if (durationtime > 0.0 && removetime > 0.0)
				{
					std::string buffer = "OnUser2 !self:TurnOff::" + std::to_string(removetime) + ":1";
					sm::sdktools::SetVariant(buffer.c_str());
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");
					sm::sdktools::AcceptEntityInput(entity, "FireUser2");
					RemoveEntity(entity, durationtime);
				}
			}

			return entity;
		}

		/**
		 * @brief Create a particle entity.
		 *
		 * @param parent            (Optional) The parent index.
		 * @param vPosition         (Optional) The origin of the spawn.
		 * @param vAngle            (Optional) The angle to the spawn.
		 * @param sAttach           (Optional) The attachment name.
		 * @param sEffect           The particle name.
		 * @param flDurationTime    (Optional) The duration of an effect.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateParticle(
			CBaseEntity* parent, Vector pos, Vector ang, 
			std::string attach, std::string effectName, float duration
		)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("info_particle_system");
			if (entity)
			{
				
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", pos);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", ang);
				sm::sdktools::DispatchKeyValue<int>(entity, "start_active", 1);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "effect_name", effectName.c_str());

				sm::sdktools::DispatchSpawn(entity);

				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (attach.size())
					{
						sm::sdktools::SetVariant(attach.c_str());
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}
				sm::sdktools::ActivateEntity(entity);
				sm::sdktools::AcceptEntityInput(entity, "Start");

				if (duration > 0.f) RemoveEntity(entity, duration);
			}
			return entity;
		}

		/**
		 * @brief Create an explosion entity.
		 *
		 * @param vPosition         The position to the spawn.
		 * @param vAngle            (Optional) The angle to the spawn.
		 * @param iFlags            (Optional) The bits with some flags.
		 * @param sSpriteName       (Optional) The sprite path.
		 * @param flDamage          (Optional) The amount of damage done by the explosion.
		 * @param flRadius          (Optional) If set, the radius in which the explosion damages entities. If unset, the radius will be based on the magnitude.
		 * @param sWeapon           (Optional) The classname defines the type of entity.
		 * @param attacker          (Optional) The attacker index.
		 * @param inflictor         (Optional) The inflictor index.
		 * @param sIgnore           (Optional) Do not harm or affect the named entity.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateExplosion(
			Vector vPosition,		int iFlags,				std::string sSpriteName,	float flDamage, float flRadius, 
			std::string sWeapon,	CBaseEntity* attacker,	CBaseEntity* inflictor,		std::string sIgnore
		)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_explosion");

			if (entity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", vPosition);
				//sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", vAngle);
				sm::sdktools::DispatchKeyValue<int>(entity, "spawnflags", iFlags);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "fireballsprite", sSpriteName.c_str());
				if (!(iFlags & ExplosionFlags::EXP_NODAMAGE))
				{
					sm::sdktools::DispatchKeyValue<const char*>(entity, "classname", sWeapon.c_str());
					sm::sdktools::DispatchKeyValue<int>(entity, "iMagnitude", std::round(flDamage));
					sm::sdktools::DispatchKeyValue<int>(entity, "iRadiusOverride", std::round(flDamage));
					if (sIgnore.size()) sm::sdktools::DispatchKeyValue<const char*>(entity, "ignoredEntity", sIgnore.c_str());
				}

				sm::sdktools::DispatchSpawn(entity);

				if (attacker) sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", attacker);
				if (inflictor) sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hInflictor", inflictor);

				sm::sdktools::AcceptEntityInput(entity, "Explode");
				sm::sdktools::AcceptEntityInput(entity, "Kill");
			}

			return entity;
		}

		/**
		 * @brief Create a point hurt entity.
		 *
		 * @param parent            (Optional) The parent index.
		 * @param vPosition         (Optional) The origin of the spawn.
		 * @param attacker          The attacker index.
		 * @param flDamage          The amount of damage inflicted.
		 * @param flRadius          The radius in which the hurt damages entities.
		 * @param iBits             (Optional) The ditfield of damage types.
		 * @param weaponID          (Optional) The weapon index or -1 for unspecified.
		 * @param sAttach           (Optional) The attachment name.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateDamage(
			CBaseEntity* parent,	Vector pos, CBaseEntity* attacker, float flDamage, 
			float flRadius,			int iBits,	int weaponID, std::string sAttach
		)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("point_hurt");
			
			if (entity)
			{
				/**
				 * The specified amount of damage will be halved.
				 * Consider multiplying your amount of damage by 2 and using it as the Value.
				 */
				int iDamage = std::round(flDamage) * 2;

				sm::sdktools::DispatchKeyValue<int>(entity, "Damage", iDamage);
				sm::sdktools::DispatchKeyValue<int>(entity, "DamageType", iBits);
				sm::sdktools::DispatchKeyValue<float>(entity, "Radius", flRadius);

				sm::sdktools::DispatchSpawn(entity);
				sm::sdktools::TeleportEntity(entity, pos, {}, {});

				sm::SetEntProp(entity, sm::Prop_Data, "m_iHammerID", weaponID);

				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);
					
					if (sAttach.size())
					{
						sm::sdktools::SetVariant(sAttach.c_str());
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}

				sm::sdktools::AcceptEntityInput(entity, "Hurt", attacker);
				sm::sdktools::AcceptEntityInput(entity, "Kill");
			}

			return entity;
		}

		/**
		 * @brief Create a sprite entity.
		 *
		 * @param parent            (Optional) The parent index.
		 * @param vPosition         (Optional) The origin of the spawn.
		 * @param vAngle            (Optional) The angle to the spawn.
		 * @param sAttach           (Optional) The attachment name.
		 * @param sSprite           The sprite path.
		 * @param sScale            The scale multiplier of the sprite.
		 * @param sRender           Set a non-standard rendering mode on this entity.
		 * @param flDurationTime    (Optional) The duration of the beam.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateSprite(
			CBaseEntity* parent, Vector pos, Vector ang, std::string sAttach, 
			std::string sSprite, float scale, int rendermode, float flDurationTime)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_sprite");

			if (entity)
			{
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", pos);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", ang);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "model", sSprite.c_str());
				sm::sdktools::DispatchKeyValue<float>(entity, "scale", scale);
				sm::sdktools::DispatchKeyValue<int>(entity, "rendermode", rendermode);

				sm::sdktools::DispatchSpawn(entity);

				sm::sdktools::ActivateEntity(entity);

				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (sAttach.size())
					{
						sm::sdktools::SetVariant(sAttach.c_str());
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}

				if (flDurationTime > 0.f) RemoveEntity(entity, flDurationTime);
			}
			return entity;
		}

		/**
		 * @brief Create a material controlller entity.
		 *
		 * @param parent            The parent index.
		 * @param sSprite           The sprite path.
		 * @param sVar              The name of the shader parameter you want to modify.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateSpriteController(CBaseEntity* parent, std::string sprite, std::string var)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("material_modify_control");

			if (entity)
			{
				sm::sdktools::DispatchKeyValue<const char*>(entity, "materialName", sprite.c_str());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "materialVar", var.c_str());

				sm::sdktools::DispatchSpawn(entity);

				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);
				}
			}

			return entity;
		}

		/**
		 * @brief Create a tesla entity.
		 *
		 * @param parent            (Optional) The parent index.
		 * @param vPosition         (Optional) The origin of the spawn.
		 * @param vAngle            (Optional) The angle to the spawn.
		 * @param sAttach           (Optional) The attachment name.
		 * @param sRadius           (Optional) The radius around the origin to find a point to strike with a tesla lightning beam.
		 * @param sSound            (Optional) The sound to be played whenever lightning is created.
		 * @param sCountMin         (Optional) The minimum number of tesla lightning beams to create when creating an arc.
		 * @param sCountMax         (Optional) The maximum number of tesla lightning beams to create when creating an arc.
		 * @param sTextureName      (Optional) The material to use for the tesla lightning beams.
		 * @param sColor            (Optional) The beam color.
		 * @param sThickMin         (Optional) The minimum width of the tesla lightning beams.
		 * @param sThinkMax         (Optional) The maximum width of the tesla lightning beams.
		 * @param sLifeMin          (Optional) The minimum lifetime of the tesla lightning beams.
		 * @param sLifeMax          (Optional) The maximum lifetime of the tesla lightning beams.
		 * @param sIntervalMin      (Optional) The minimum time delay between random arcing.
		 * @param sIntervalMax      (Optional) The maximum time delay between random arcing.
		 * @param flDurationTime    (Optional) The duration of the beam.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* UTIL_CreateTesla(
			CBaseEntity* parent,	Vector pos,			Vector ang,				std::string attach,			float radius, 
			std::string sSound,		int countMin,		int countMax,			std::string sTextureName,	Color color,
			float ThickMin,			float ThickMax,		float LifeMin,			float LifeMax,				float flIntervalMin, 
			float flIntervalMax,	float flDurationTime
		)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("point_tesla");

			if (entity)
			{
				// Dispatch main values of the entity
				sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", pos);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", ang);
				sm::sdktools::DispatchKeyValue<float>(entity, "m_flRadius", radius);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "m_SoundName", sSound.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "beamcount_min", countMin);
				sm::sdktools::DispatchKeyValue<int>(entity, "beamcount_max", countMax);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "texture", sTextureName.c_str());
				std::string ColorBuffer = std::string() + std::to_string(color.r()) + " " + std::to_string(color.g()) + " " + std::to_string(color.b());
				sm::sdktools::DispatchKeyValue<const char*>(entity, "m_Color", ColorBuffer.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "thick_min", ThickMin);
				sm::sdktools::DispatchKeyValue<int>(entity, "thick_max", ThickMax);
				sm::sdktools::DispatchKeyValue<int>(entity, "lifetime_min", LifeMin);
				sm::sdktools::DispatchKeyValue<int>(entity, "lifetime_max", LifeMax);
				sm::sdktools::DispatchKeyValue<float>(entity, "interval_min", flIntervalMin);
				sm::sdktools::DispatchKeyValue<float>(entity, "interval_max", flIntervalMax);

				// Spawn the entity into the world
				sm::sdktools::DispatchSpawn(entity);

				// Activate the entity
				sm::sdktools::ActivateEntity(entity);
				sm::sdktools::AcceptEntityInput(entity, "TurnOn");
				sm::sdktools::AcceptEntityInput(entity, "DoSpark");

				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (attach.size())
					{
						sm::sdktools::SetVariant(attach.c_str());
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}

				if (flDurationTime > 0.f) RemoveEntity(entity, flDurationTime);
			}

			return entity;
		}

		/**
		 * @brief Create a shooter entity.
		 *
		 * @param parent            The parent index.
		 * @param sAttach           The attachment bone of the entity parent.
		 * @param sRender           (Optional) Used to set a non-standard rendering mode on this entity. See also 'FX Amount' and 'FX Color'.
		 * @param sSound            (Optional) Material Sound. (-1: None | 0: Glass | 1: Wood | 2: Metal | 3: Flesh | 4: Concrete)
		 * @param iSkin             (Optional) Some models have multiple skins.
		 * @param sTextureName      Thing to shoot out. Can be a .mdl (model) or a .vmt (material/sprite).
		 * @param vAngle            (Optional) The direction the gibs will fly.
		 * @param vGibAngle         (Optional) The orientation of the spawned gibs.
		 * @param iGibs             The number of gibs - Total number of gibs to shoot each time it's activated
		 * @param flDelay           The delay (in seconds) between shooting each gib. If 0, all gibs shoot at once.
		 * @param flVelocity        The speed of the fired gibs.
		 * @param flVariance        How much variance in the direction gibs are fired.
		 * @param flLife            Time in seconds for gibs to live +/- 5%.
		 * @param flDurationTime    The duration of the gibs.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* UTIL_CreateShooter(
		CBaseEntity* parent,		std::string sAttach,	int iRender,		int iSound,		int iSkin, 
		std::string sTextureName,	Vector vAngle,			Vector vGibAngle,	float iGibs,	float flDelay,
		float flVelocity,			float flVariance,		float flLife,		float flDurationTime
		)
		{
			// Create a shooter entity
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_shooter");

			// Validate entity
			if (entity)
			{
				//sm::sdktools::DispatchKeyValue<Vector>(entity, "origin", vPosition);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "angles", vAngle);
				sm::sdktools::DispatchKeyValue<Vector>(entity, "gibangles", vGibAngle);
				sm::sdktools::DispatchKeyValue<int>(entity, "rendermode", iRender);
				//std::string ColorBuffer = std::string() + std::to_string(color.r()) + " " + std::to_string(color.g()) + " " + std::to_string(color.b());
				//sm::sdktools::DispatchKeyValue<const char*>(entity, "rendercolor", ColorBuffer);
				//sm::sdktools::DispatchKeyValue<int>(entity, "renderfx", iRenderFX);
				sm::sdktools::DispatchKeyValue<int>(entity, "shootsounds", iSound);
				sm::sdktools::DispatchKeyValue<const char*>(entity, "shootmodel", sTextureName.c_str());
				sm::sdktools::DispatchKeyValue<int>(entity, "skin", iSkin);
				sm::sdktools::DispatchKeyValue<float>(entity, "delay", flDelay);
				sm::sdktools::DispatchKeyValue<float>(entity, "m_flVelocity", flVelocity);
				sm::sdktools::DispatchKeyValue<float>(entity, "m_flVariance", flVariance);
				sm::sdktools::DispatchKeyValue<float>(entity, "m_flGibLife", flLife);

				sm::sdktools::DispatchSpawn(entity);

				sm::sdktools::ActivateEntity(entity);
				sm::sdktools::AcceptEntityInput(entity, "Shoot");

				sm::sdktools::SetVariant("!activator");
				sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
				sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

				if (sAttach.size())
				{
					sm::sdktools::SetVariant(sAttach.c_str());
					sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
				}

				RemoveEntity(entity, flDurationTime);
			}

			// Return on the success
			return entity;
		}

		/**
		 * @brief Create a beam entity.
		 *
		 * @param vStartPosition    The start position of the beam.
		 * @param vEndPosition      The end position of the beam.
		 * @param sDamage           (Optional) How much damage this beam does per second to things it hits when it is continually on, or instantaneously if it strikes. For continuous damage, the value should be greater than 10 or it may not work.
		 * @param sFrame            (Optional) The framerate at which the beam texture should animate, if it has multiple frames.
		 * @param sWidth            (Optional) The pixel width of the beam. Range: 1 to MAX_BEAM_WIDTH.
		 * @param sRenderFX         (Optional) The several GoldSrc-era visibility modes which change the way the entity is rendered, typically by fading it in and out.
		 * @param sType             (Optional) If you want the beam to fire an output when touched by entities, choose the entity type here. (0: Not a tripwire | 1: Player Only | 2: NPC Only | 3: Player or NPC | 4: Player or NPC or Physprop)
		 * @param sRate             (Optional) The framerate at which the beam texture should animate, if it has multiple frames.
		 * @param sDecalName        (Optional) The decal to be applied at the end of the beam
		 * @param sScroll           (Optional) The rate at which the beam texture should scroll along the beam. Range: 0 to MAX_BEAM_SCROLLSPEED.
		 * @param sScale            (Optional) The float value to multiply sprite color by when running in HDR mode.
		 * @param sTextureName      (Optional) The material used to draw the beam.
		 * @param sLife             (Optional) The amount of time before the beam dies. Setting to zero will make the beam stay forever.
		 * @param sStrike           (Optional) The refire time between random strikes of the beam. Only used if the 'Random Strike' spawnflag is set.
		 * @param iFlags            (Optional) The bits with some flags.
		 * @param sAmplitude        (Optional) The amount of noise in the beam. 0 is a perfectly straight beam. Range: 0 to MAX_BEAM_NOISEAMPLITUDE.
		 * @param sRadius           (Optional) If the LightningStart and/or LightningEnd values are omitted, this radius determines the area within which the endpoints will randomly strike. A new random position will be appointed for every strike.
		 * @param sRenderAMT        (Optional) The beam brightness. Useless when set to 0.
		 * @param sColor            The beam color.
		 * @param flDelayTime       The delay after the touch.
		 * @param flDurationTime    The duration of the beam.
		 * @param sName             The name of the beam.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateBeam(
			Vector vStartPosition, Vector vEndPosition, int iDamage, int iFrame, float flWidth, int iRenderFX, int iType,
			int iRate, std::string DecalName, int iScroll, float flScale, std::string TextureName, std::string sLife, std::string sStrike,
			int iFlags, float flAmplitude, int iRadius, int iRenderAMT, Color color, float flDelayTime, float flDurationTime, std::string sName
		)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("env_beam");
			if (entity)
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

					sm::sdktools::SetVariant(VariantBuffer.c_str());
					sm::sdktools::AcceptEntityInput(entity, "AddOutput");

					VariantBuffer = "OnUser2 !self:TurnOn::" + std::to_string(flDelayTime) + ":1";
					sm::sdktools::SetVariant(VariantBuffer.c_str());
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
		/**
		 * @brief Create a light dynamic entity.
		 *
		 * @param parent            (Optional) The parent index.
		 * @param vPosition         (Optional) The origin of the spawn.
		 * @param sAttach           (Optional) The attachment name.
		 * @param sInnerCone        (Optional) The inner (bright) angle.
		 * @param sCone             (Optional) The outer (fading) angle.
		 * @param sBrightness       (Optional) The intensity of the spotlight.
		 * @param sPitch            (Optional) Used instead of Pitch Yaw Roll's value for reasons unknown.
		 * @param sStyle            (Optional) The lightstyle (see Appearance field for possible values).
		 * @param iFlags            (Optional) The bits with some flags.
		 * @param sColor            The color of the light. (RGBA)
		 * @param flDistance        The distance of the light.
		 * @param flRadius          The radius of the light.
		 * @param flDurationTime    (Optional) The duration of the light.
		 *
		 * @return                  The entity index.
		 **/
		inline CBaseEntity* CreateLight(
			CBaseEntity* parent, Vector vPosition, std::string attach, int iInnerCone, int iCone,
			int iBrightness, int iPitch, int iStyle, int iFlags, Color color, float flDistance, float flRadius, float flDurationTime
			)
		{
			CBaseEntity* entity = sm::sdktools::CreateEntityByName("light_dynamic");

			if (entity)
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
				
				if (parent)
				{
					sm::sdktools::SetVariant("!activator");
					sm::sdktools::AcceptEntityInput(entity, "SetParent", parent, entity);
					sm::SetEntPropEnt(entity, sm::Prop_Data, "m_hOwnerEntity", parent);

					if (attach.size())
					{
						sm::sdktools::SetVariant(attach.c_str());
						sm::sdktools::AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
					}
				}
				if (flDurationTime > 0.f) RemoveEntity(entity, flDurationTime);
			}

			return entity;
		}

		/**
		 * @brief Sets the glowing on the entity.
		 *
		 * @param entity            The entity index.
		 * @param enableState       Sets to true to enable glowing, false to disable.
		 * @param iType             (Optional) The type of the glowing.
		 * @param iRed              (Optional) Amount of a red (0-255)
		 * @param iGreen            (Optional) Amount of a green (0-255)
		 * @param iBlue             (Optional) Amount of a blue (0-255)
		 * @param iAlpha            (Optional) Amount of an alpha (0-255)
		 **/
		inline void CreateGlowing(CBaseEntity* entity, bool enableState, int iType = 0, int iRed = 255, int iGreen = 255, int iBlue = 255, int iAlpha = 255)
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

		/**
		 * @brief Sets the render of a entity.
		 *
		 * @param entity            The entity index.
		 * @param color             The offset index.
		 * @param iRender           The render amount.
		 **/
		inline void SetRenderColor(CBaseEntity* entity, RenderColorType_t color, int iRender)
		{
			static int renderoffset = 0;
			if (!renderoffset && (renderoffset = sm::GetEntSendPropOffs(entity, "m_clrRender")) == -1) return;

			sm::SetEntProp<int>(entity, sm::Prop_Send, "m_nRenderMode", RenderMode_t::kRenderTransAlpha);
			sm::SetEntData<int>(entity, renderoffset + static_cast<int>(color), iRender, 1, true);
		}

		/**
		 * @brief Gets the render of a entity.
		 *
		 * @param entity            The entity index.
		 * @param color             The offset index.
		 * @return                  The render amount.
		 **/
		inline int GetRenderColor(CBaseEntity* entity, RenderColorType_t color)
		{
			static int renderoffset = 0;
			if (!renderoffset && (renderoffset = sm::GetEntSendPropOffs(entity, "m_clrRender")) == -1) return 255;
			return sm::GetEntData<int>(entity, renderoffset + static_cast<int>(color), 1);
		}

		/**
		 * @brief Create the tracer to a entity. (*not client)
		 *
		 * @param parent            The parent index.
		 * @param sAttach           The attachment name.
		 * @param sEffect           The effect name.
		 * @param vBullet           The position of a bullet hit.
		 * @param flDurationTime    The duration of life.
		 **/
		inline void CreateTracer(CBaseEntity* parent, std::string attach, std::string effect, Vector bullet, float duration)
		{

		}

		/**
		 * @brief Shake a client screen with specific parameters.
		 *
		 * @param client            The client index.
		 * @param flAmplitude       The amplitude of shake.
		 * @param flFrequency       The frequency of shake.
		 * @param flDurationTime    The duration of shake in the seconds.
		 **/
		inline void CreateShakeScreen(CBasePlayer* client, float flAmplitude, float flFrequency, float flDurationTime)
		{
			return sm::hudtext::CreateShakeScreen(sm::ent_cast<int>(client), flAmplitude, flFrequency, flDurationTime);
		}

		/**
		 * @brief Push a client with specific parameters.
		 *
		 * @param client            The client index.
		 * @param vPosition         The force origin.
		 * @param vOrigin           The client origin.
		 * @param flDistance        The distance amount.
		 * @param flForce           The force amount.
		 * @param flRadius          The radius amount.
		 **/
		//inline void UTIL_CreateFadeScreen(int client, float flDuration, float flHoldTime, int iFlags, int vColor[4])
		
		/**
		 * @brief Push a client with specific parameters.
		 *
		 * @note Looks like can be expand to the whole CBaseEntity(if movable).
		 * Try it on.
		 * @param client            The client index.
		 * @param vPosition         The force origin.
		 * @param vOrigin           The client origin.
		 * @param flDistance        The distance amount.
		 * @param flForce           The force amount.
		 * @param flRadius          The radius amount.
		 **/
		inline void UTIL_CreatePhysForce(
			CBaseEntity* entity, Vector vPosition, Vector vOrigin, 
			float flDistance, float flForce, float flRadius
		)
		{
			Vector vVelocity = vOrigin - vPosition;

			float flKnockback = flForce * (1.0 - (flDistance / flRadius));
			vVelocity.Normalized();
			float flMagnitude = vVelocity.Length();
			float flScaleFactor = std::sqrt(std::pow(flKnockback, 2) / flMagnitude);
			vVelocity.z *= flForce;
			sm::sdktools::TeleportEntity(entity, {}, {}, vVelocity);
		}

		// DO NOT USE HERE.
		//inline void UTIL_CreateClientHint(int client, char[] sMessage)
		
		// DO NOT USE HERE.
		//inline void UTIL_CreateClientHud(Handle hSync, int client, float x, float y, float holdTime, int r, int g, int b, int a, int effect, float fxTime, float fadeIn, float fadeOut, char[] sMessage)
		
		/**
		 * @brief Precache models and also adding them into the downloading table.
		 * 
		 * @param sModel            The model path.
		 *
		 * @return                  The model index.
		 **/
		inline int UTIL_PrecacheModel(std::string sModel)
		{

		}

		/**
		 * @brief Ignites the entity on a fire.
		 *
		 * @param entity            The entity index.
		 * @param flDurationTime    The number of seconds to set on a fire.
		 **/
		inline void UTIL_IgniteEntity(CBaseEntity* entity, float flDurationTime)
		{

		}

		/**
		 * @brief Extinguishes the entity that is on a fire.
		 *
		 * @param entity            The entity index.
		 **/
		inline void UTIL_ExtinguishEntity(CBaseEntity* entity)
		{

		}
		/**
		 * @brief Remove the entity from a world after some delay.
		 *
		 * @param entity            The entity index.
		 * @param flDelayTime       The number of seconds to kill an entity.
		 **/
		inline void RemoveEntity(CBaseEntity* entity, float flDelayTime)
		{
			//FormatEx(sFlags, sizeof(sFlags), "OnUser1 !self:Kill::%f:1", flDelayTime);
			//std::string buffer = "OnUser1 !self:Kill::" + std::to_string(flDelayTime) + ":1";
			//sm::PrintToChatAll(buffer.c_str());
			char buffer[32];
			smutils->Format(buffer, sizeof(buffer), "OnUser1 !self:Kill::%f:1", flDelayTime);
			sm::sdktools::SetVariant(buffer);
			sm::sdktools::AcceptEntityInput(entity, "AddOutput");
			sm::sdktools::AcceptEntityInput(entity, "FireUser1");
		}

		/**
		 * @brief Precache decals and also adding them into the downloading table.
		 *
		 * @param sDecal            The decal path.
		 *
		 * @return                  The decal index.
		 **/
		//inline void UTIL_PrecacheDecal(char[] sDecal)

		/**
		 * @brief Precache sounds and also adding them into the downloading table.
		 *
		 * @param soundPath         The sound path.
		 **/
		//inline void UTIL_PrecacheSound(char[] sSound)

		/**
		 * @brief Find the trace hull intersection.
		 *
		 * @param hTrace            The trace handle.
		 * @param vPosition         The entity position.
		 * @param vMins             The mins vector.
		 * @param vMaxs             The maxs vector.
		 * @param filter            The function to use as a filter.
		 * @param data              The data value to pass through to the filter function.
		 **/
		//inline void UTIL_FindHullIntersection(Handle &hTrace, float vPosition[3], const float vMins[3], const float vMaxs[3], TraceEntityFilter filter, any data)
		
		/**
		 * @brief Gets the velocity and it's angle from the two vectors.
		 *
		 * @param vStartPosition    The starting position.
		 * @param vEndPosition      The ending position.
		 * @param vAngle            The calculated angle's vector output.
		 * @param vVelocity         The calculated velocity's vector output.
		 * @param flSpeedScale      (Optional) The speed scale value.
		 * @param verticalScale     (Optional) Set to true for reversing vertical velocity's value, false to reset.
		 **/
		//inline void UTIL_GetVelocityByAim(float vStartPosition[3], float vEndPosition[3], float vAngle[3], float vVelocity[3], float flSpeedScale = 1.0, bool verticalScale = false)
		
		//inline bool UTIL_IsOnSamePlane(int entity, int target, float vPosition[3], TraceEntityFilter filter)
		
		//inline bool UTIL_GetTraceEndPoint(int entity, float vPosition[3])
		
		//inline bool UTIL_TraceRay(int entity, int target, float vStartPosition[3], float vEndPosition[3], TraceEntityFilter filter)
		
		/**
		 * @brief Calculates the distance between two entities.
		 *
		 * @param client            The client index.
		 * @param entity            The entity index.
		 *
		 * @return                  The distance amount.
		 **/
		//inline float UTIL_GetDistanceBetween(int client, int entity)
		
		/**
		 * @brief Searches for the index of a given string in a dispatch table.
		 *
		 * @param sEffect           The effect name.
		 *
		 * @return                  The string index.
		 **/
		//inline int GetEffectIndex(char[] sEffect)
		
		/**
		 * @brief Searches for the index of a given string in an effect table.
		 *
		 * @param sEffect           The effect name.
		 *
		 * @return                  The string index.
		 **/
		//inline int GetParticleEffectIndex(char[] sEffect)
		
		/**
		 * @brief Precache the particle in the effect table. (for client)
		 *
		 * @param client            (Optional) The client index.
		 * @param sEffect           The effect name.
		 **/
		//inline void PrecacheParticleFile(int client = 0, char[] sEffect)
		
		/**
		 * @brief Precache the particle in the effect table.
		 *
		 * @param sEffect           The effect name.
		 **/
		//inline void PrecacheParticleEffect(char[] sEffect)
		
		/**
		 * @brief Gets a string of a given index in a dispatch table.
		 *
		 * @param iIndex            The string index.
		 * @param sEffect           The string to return effect in.
		 * @param iMaxLen           The lenght of string.
		 **/
		//inline void GetEffectName(int iIndex, char[] sEffect, int iMaxLen)
		
		/**
		 * @brief Gets a string of a given index in an effect table.
		 *
		 * @param iIndex            The string index.
		 * @param sEffect           The string to return effect in.
		 * @param iMaxLen           The lenght of string.
		 **/
		//inline void GetParticleEffectName(int iIndex, char[] sEffect, int iMaxLen)
		
		/**
		 * @brief Gets a string count in a dispatch table.
		 *
		 * @return                  The table size.
		 **/
		//inline void GetEffectNameCount(/*void*/)
		
		/**
		 * @brief Gets a string count in an effect table.
		 *
		 * @return                  The table size.
		 **/
		//inline int GetParticleEffectCount();
		
		//inline bool PlayersFilter(int entity, int contentsMask)
	}
}