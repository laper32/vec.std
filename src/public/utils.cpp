#include "utils.h"
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
				sm::sdktools::DispatchKeyValue(pEntity, "origin", position);
				sm::sdktools::DispatchKeyValue(pEntity, "angles", angle);
				sm::sdktools::DispatchKeyValue(pEntity, "targetname", classname.c_str());
				sm::sdktools::DispatchKeyValue(pEntity, "target", path.c_str());
				sm::sdktools::DispatchKeyValue(pEntity, "speed", speed);
				sm::sdktools::DispatchKeyValue(pEntity, "wheels", 256); // Make moving smoother
				sm::sdktools::DispatchKeyValue(pEntity, "bank", 20); // Make turning smoother
				sm::sdktools::DispatchKeyValue(pEntity, "orientationtype", 2); // Linear blend, add some smoothness
				sm::sdktools::DispatchKeyValue(pEntity, "spawnflags", flags); 
				if (!sound.size()) sm::sdktools::DispatchKeyValue(pEntity, "MoveSound", sound.c_str());
				 
				// UTIL_SetRenderColor

				sm::sdktools::DispatchSpawn(pEntity);

			}
			return pEntity;
		}

		inline CBaseEntity* CreatePath(std::string classname, Vector position, Vector angle, std::string NextTarget, int flag)
		{
			return nullptr;
		}

		inline CBaseEntity* CreateMonster(std::string classname, Vector position, Vector angle, std::string sModel, int iFlags)
		{
			return nullptr;
		}

		inline CBaseEntity* CreatePhysics(std::string classname, Vector position, Vector angle, std::string model, int flags)
		{
			return nullptr;
		}

		inline CBaseEntity* CreateDynamic(std::string classname, Vector position, Vector angle, std::string model, std::string defaultAnim, bool bOverride, bool bHoldAnim, bool bSolid, int iFlags)
		{
			return nullptr;
		}

		inline CBaseEntity* CreateProjectile(Vector pos, Vector ang, std::string model)
		{
			return nullptr;
		}

		inline CBaseEntity* CreateSmoke(CBaseEntity* parent, Vector pos, Vector ang, std::string attach, int spradbase, int spradspeed, int speed, int startsize, int endsize, int density, int length, int twist, Color color, int transparency, std::string spritename, float removetime, float durationtime)
		{
			return nullptr;
		}

		inline CBaseEntity* CreateParticle(CBaseEntity* parent, Vector pos, Vector ang, std::string attach, std::string effectName, float duration)
		{
			return nullptr;
		}

		inline CBaseEntity* CreateExplosion(Vector vPosition, int iFlags, std::string sSpriteName, float flDamage, float flRadius, std::string sWeapon, CBaseEntity* attacker, CBaseEntity* inflictor, std::string sIgnore)
		{
			return nullptr;
		}

		inline CBaseEntity* UTIL_CreateDamage(CBaseEntity* parent, Vector pos, int attacker, float flDamage, float flRadius, int iBits, int weaponID, std::string sAttach)
		{
			return nullptr;
		}

		inline CBaseEntity* UTIL_CreateSprite(CBaseEntity* parent, Vector pos, Vector ang, std::string sAttach, std::string sSprite, float scale, int rendermode, float flDurationTime)
		{
			return nullptr;
		}
	}
}