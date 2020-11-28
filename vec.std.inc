#if defined _vec_std_included
#endinput
#endif

#define _vec_std_included

native void ToolsSetVelocity(int entity, float velocity[3]);

native void ToolsGetVelocity(int entity, float velocity[3], bool apply = true, bool stack = true);

native float GetSpeed(int entity);

native void ToolsGetAbsOrigin(int entity, float origin[3]);

native void ToolsGetAbsAngles(int entity, float angles[3]);

// ToolsGetMyWeapons(int entity);

// ToolsGetWeapon(int entity);

native int ToolsGetHealth(int entity);

native void ToolsSetHealth(int entity, int val);

native float ToolsGetLMV(int entity);

native void ToolsSetLMV(int entity, void val);

native int ToolsGetArmor(int entity);

native void ToolsSetArmor(int entity, int val);

native int ToolsGetTeam(int entity);

native void ToolsSetTeam(int entity, int team);

native bool ToolsGetNightVision(int entity, bool ownership = false);

native void ToolsSetNightVision(int entity, bool enable, bool ownership = false);

native bool ToolsGetDefuser(int entity);

native void ToolsSetDefuser(int entity, bool enable);

native bool ToolsGetHelmet(int entity);
native void ToolsSetHelmet(int entity, bool enable);

native bool ToolsGetHeavySuit(int entity);
native void ToolsSetHeavySuit(int entity, bool enable);

//ToolsGetActiveWeapon
//ToolsSetActiveWeapon

native int ToolsGetAddonBits(int entity);
native void ToolsSetAddonBits(int entity, int val);
//ToolsGetObserverMode
//ToolsGetObserverTarget

native int ToolsGetHitGroup(int entity);

native int ToolsGetFrags(int entity);
native void ToolsSetFrags(int entity, int val);

native int ToolsGetDeaths(int entity);
native void ToolsSetDeaths(int entity, int val);

native void ToolsSetGravity(int entity, float val);

//ToolsSetSpot

native void ToolsSetDetecting(int entity, bool enable);

//ToolsSetHud

//ToolsSetArm

native void ToolsSetAttack(int entity, float val);

native void ToolsSetFlashLight(int entity, bool enable);

native void ToolsSetFov(int entity, int val = 90);

native void ToolsSetTextures(int entity, int body = -1, int skin = -1);

native int ToolsGetEffect(int entity);

native void ToolsSetEffect(int entity, int val);

//ToolsGetActivator

native void ToolsSetModelIndex(int entity, int model);

//ToolsGetOwner
//ToolsSetOwner
//ToolsGetParent
//ToolsSetParent
//ToolsGetRagdollIndex
native int ToolsGetCollisionGroup(int entity);
native void ToolsSetCollisionGroup(int entity, int val);