#if defined _vec_std_utils_included
#endinput
#endif
#define _vec_std_utils_included

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
 * @return                  The entity index.                       
 **/
native int UTIL_CreateTrain(
    char[] sClassname, float vPosition[3], float vAngle[3], 
    char[] sPath, char[] sSpeed, char[] sSound = "", int iFlags = 0);

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
native int UTIL_CreatePath(char[] sClassname, float vPosition[3], float vAngle[3], char[] sNextTarget, int iFlags = 0);

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
native int UTIL_CreatePhysics(char[] sClassname, float vPosition[3], float vAngle[3], char[] sModel, int iFlags = 0);

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
native int UTIL_CreateDynamic(
    char[] sClassname, float vPosition[3], float vAngle[3], char[] sModel, 
    char[] sDefaultAnim = "", bool bOverride = true, bool bHoldAnim = false, bool bSolid = false, int iFlags = DYN_COLLISIONDISABLED);

/**
 * @brief Create a projectile entity.
 * 
 * @param vPosition         The position to the spawn.
 * @param vAngle            The angle to the spawn.
 * @param sModel            (Optional) The model path.
 *
 * @return                  The entity index.                       
 **/
native int UTIL_CreateProjectile(float vPosition[3], float vAngle[3], char[] sModel = "");

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
// later on will re-clearify the variable typename.
native int UTIL_CreateSmoke(
    int parent = 0, float vPosition[3] = NULL_VECTOR, float vAngle[3] = NULL_VECTOR, 
    char[] sAttach = "", char[] sSpreadBase = "100", char[] sSpreadSpeed = "70", char[] sSpeed = "80", 
    char[] sStartSize = "200", char[] sEndSize = "2", char[] sDensity = "30", char[] sLength = "400", 
    char[] sTwist = "20", char[] sColor, char[] sTransparency, char[] sSpriteName, float flRemoveTime = 0.0, float flDurationTime = 0.0);


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
native int UTIL_CreateMonster(char[] sClassname, float vPosition[3], float vAngle[3], char[] sModel, int iFlags = 0);

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
native int UTIL_CreateParticle(
    int parent, float vPosition[3] = NULL_VECTOR, float vAngle[3] = NULL_VECTOR, 
    char[] sAttach = "", char[] sEffect, float flDurationTime = 0.0);

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
native int UTIL_CreateExplosion(float vPosition[3]/*, float vAngle[3] = NULL_VECTOR*/, int iFlags = 0, 
                                char[] sSpriteName = "materials/sprites/xfireball3.vmt", float flDamage = 0.0, float flRadius = 0.0, 
                                char[] sWeapon = "", int attacker = -1, int inflictor = -1, char[] sIgnore = "");

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
native int UTIL_CreateDamage(int parent = 0, float vPosition[3] = NULL_VECTOR, int attacker, float flDamage, 
                            float flRadius, int iBits = DMG_GENERIC, int weaponID = -1, char[] sAttach = "");

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
native int UTIL_CreateSprite(int parent = 0, float vPosition[3] = NULL_VECTOR, 
                            float vAngle[3] = NULL_VECTOR, char[] sAttach = "", char[] sSprite, char[] sScale, 
                            char[] sRender, float flDurationTime = 0.0);

/**
 * @brief Create a material controlller entity.
 * 
 * @param parent            The parent index. 
 * @param sSprite           The sprite path.
 * @param sVar              The name of the shader parameter you want to modify.
 *
 * @return                  The entity index.
 **/
native int UTIL_CreateSpriteController(int parent, char[] sSprite, char[] sVar);

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
native int UTIL_CreateTesla(int parent = 0, float vPosition[3] = NULL_VECTOR, float vAngle[3] = NULL_VECTOR, 
                            char[] sAttach = "", char[] sRadius = "500.0", char[] sSound = "DoSpark", char[] sCountMin = "42", 
                            char[] sCountMax = "62", char[] sTextureName = "materials/sprites/physbeam.vmt", 
                            char[] sColor = "255 255 255", char[] sThickMin = "10.0", char[] sThickMax = "11.0", 
                            char[] sLifeMin = "0.3", char[] sLifeMax = "0.3", char[] sIntervalMin = "0.1", 
                            char[] sIntervalMax = "0.2", float flDurationTime = 0.0);

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
native int UTIL_CreateShooter(
    int parent, char[] sAttach, char[] sRender = "5", char[] sSound = "-1", int iSkin = 0, 
    char[] sTextureName, float vAngle[3] = NULL_VECTOR, float vGibAngle[3] = NULL_VECTOR, 
    float iGibs, float flDelay, float flVelocity, float flVariance, float flLife, float flDurationTime);

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
native int UTIL_CreateBeam(float vStartPosition[3], float vEndPosition[3], char[] sDamage = "0", char[] sFrame = "0", 
                            char[] sWidth = "4.0", char[] sRenderFX = "0", char[] sType = "3", char[] sRate = "0", 
                            char[] sDecalName = "Bigshot", char[] sScroll = "35", char[] sScale = "1.0", 
                            char[] sTextureName = "materials/sprites/purplelaser1.vmt", char[] sLife = "0", char[] sStrike = "1", 
                            int iFlags = 0, char[] sAmplitude = "0", char[] sRadius = "256", char[] sRenderAMT = "100", char[] sColor, 
                            float flDelayTime, float flDurationTime, char[] sName);

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
native int UTIL_CreateLight(
    int parent = 0,         float vPosition[3] = NULL_VECTOR,   char[] sAttach = "",    int iInnerCone = 0, 
    int iCone = 80,         int iBrightness = 1,                int iPitch = 90,        int iStyle = 1,
    int iFlags = 0,         char[] sColor,                      float flDistance,       float flRadius,
    float flDurationTime = 0.0);

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
native void UTIL_CreateGlowing(int entity, bool enableState, int iType = 0, int iRed = 255, int iGreen = 255, int iBlue = 255, int iAlpha = 255);

/**
 * @brief Sets the render of a entity.
 *
 * @param entity            The entity index.
 * @param color             The offset index.
 * @param iRender           The render amount.
 **/
native void UTIL_SetRenderColor(int entity, RenderingColorType color, int iRender);

/**
 * @brief Gets the render of a entity.
 *
 * @param entity            The entity index.
 * @param color             The offset index.
 * @return                  The render amount.
 **/
native int UTIL_GetRenderColor(int entity, RenderingColorType color);

/**
 * @brief Create the tracer to a entity. (*not client)
 *
 * @param parent            The parent index.
 * @param sAttach           The attachment name.
 * @param sEffect           The effect name.
 * @param vBullet           The position of a bullet hit.
 * @param flDurationTime    The duration of life.
 **/
native void UTIL_CreateTracer(int parent, char[] sAttach, char[] sEffect, float vBullet[3], float flDurationTime);

/**
 * @brief Shake a client screen with specific parameters.
 * 
 * @param client            The client index.
 * @param flAmplitude       The amplitude of shake.
 * @param flFrequency       The frequency of shake.
 * @param flDurationTime    The duration of shake in the seconds.
 **/
native void UTIL_CreateShakeScreen(int client, float flAmplitude, float flFrequency, float flDurationTime);

/**
 * @brief Fade a client screen with specific parameters.
 * 
 * @param client            The client index.
 * @param flDuration        The duration of fade in the seconds.
 * @param flHoldTime        The holding time of fade in the seconds.
 * @param iFlags            The bits with some flags.
 * @param vColor            The array with RGB color.
 **/
native void UTIL_CreateFadeScreen(int client, float flDuration, float flHoldTime, int iFlags, int vColor[4]);

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
native void UTIL_CreatePhysForce(int client, float vPosition[3], float vOrigin[3], float flDistance, float flForce, float flRadius);

/**
 * @brief Send a hint message to the client screen with specific parameters.
 * 
 * @param client            The client index.
 * @param sMessage          The message to send.
 **/
// native void UTIL_CreateClientHint(int client, char[] sMessage)

//native void UTIL_CreateClientHud(Handle hSync, int client, float x, float y, float holdTime, int r, int g, int b, int a, int effect, float fxTime, float fadeIn, float fadeOut, char[] sMessage)

/**
 * @brief Precache models and also adding them into the downloading table.
 * 
 * @param sModel            The model path.
 *
 * @return                  The model index.
 **/
native int UTIL_PrecacheModel(char[] sModel);

/**
 * @brief Ignites the entity on a fire.
 * 
 * @param entity            The entity index. 
 * @param flDurationTime    The number of seconds to set on a fire.
 **/
native void UTIL_IgniteEntity(int entity, float flDurationTime);

/**
 * @brief Extinguishes the entity that is on a fire.
 * 
 * @param entity            The entity index. 
 **/
native void UTIL_ExtinguishEntity(int entity);

/**
 * @brief Remove the entity from a world after some delay.
 * 
 * @param entity            The entity index. 
 * @param flDelayTime       The number of seconds to kill an entity.
 **/
native void UTIL_RemoveEntity(int entity, float flDelayTime);

/**
 * @brief Precache decals and also adding them into the downloading table.
 * 
 * @param sDecal            The decal path.
 *
 * @return                  The decal index.
 **/
native void UTIL_PrecacheDecal(char[] sDecal);
/**
 * @brief Precache sounds and also adding them into the downloading table.
 * 
 * @param soundPath         The sound path.
 **/
native void UTIL_PrecacheSound(char[] sSound);

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
native void UTIL_FindHullIntersection(Handle &hTrace, float vPosition[3], const float vMins[3], const float vMaxs[3], TraceEntityFilter filter, any data);

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
native void UTIL_GetVelocityByAim(float vStartPosition[3], float vEndPosition[3], float vAngle[3], float vVelocity[3], float flSpeedScale = 1.0, bool verticalScale = false);

/**
 * @brief Validate that the entity is can see the target.
 *
 * @note Check 3 spots, or else when standing right next to someone looking at their eyes, 
 *       the angle will be too great to see their center. Thank to Pelipoika.
 *
 * @note This should be a validation that whether on same plane, not can see each other.
 * 		 To check whether can need, an intersection test is required.
 *
 * @param entity            The entity index. 
 * @param target            The target index. 
 * @param vPosition         The entity position.
 * @param filter            The function to use as a filter.
 *
 * @return                  True of false.        
 **/
native bool UTIL_IsOnSamePlane(int entity, int target, float vPosition[3], TraceEntityFilter filter);

/**
 * @brief Gets the End of the point what the entity traces to.
 *
 * @param entity            The entity index.
 * @param vPosition         The position of the ray.
 *
 * @return                  T/F.
 */
native bool UTIL_GetTraceEndPoint(int entity, float vPosition[3]);

/**
 * @brief Starts up a new trace ray using a new trace result and a customized trace ray filter. 
 *
 * @param entity            The entity index.
 * @param target            The target index. 
 * @param vStartPosition    The starting position of the ray.
 * @param vEndPosition      The ending position of the ray.
 * @param filter            The function to use as a filter.
 *
 * @return                  True of false.        
 **/
native bool UTIL_TraceRay(int entity, int target, float vStartPosition[3], float vEndPosition[3], TraceEntityFilter filter);

/**
 * @brief Calculates the distance between two entities.
 *
 * @param client            The client index. 
 * @param entity            The entity index.
 *
 * @return                  The distance amount.        
 **/
native float UTIL_GetDistanceBetween(int client, int entity);

/**
 * @brief Searches for the index of a given string in a dispatch table.
 *
 * @param sEffect           The effect name.
 *
 * @return                  The string index.
 **/
native int UTIL_GetEffectIndex(char[] sEffect);

/**
 * @brief Searches for the index of a given string in an effect table.
 *
 * @param sEffect           The effect name.
 *
 * @return                  The string index.
 **/
native int UTIL_GetParticleEffectIndex(char[] sEffect);

/**
 * @brief Precache the particle in the effect table. (for client)
 *
 * @param client            (Optional) The client index.
 * @param sEffect           The effect name.
 **/
native void UTIL_PrecacheParticleFile(int client = 0, char[] sEffect);

/**
 * @brief Precache the particle in the effect table.
 *
 * @param sEffect           The effect name.
 **/
native void UTIL_PrecacheParticleEffect(char[] sEffect);

/**
 * @brief Gets a string of a given index in a dispatch table.
 *
 * @param iIndex            The string index.
 * @param sEffect           The string to return effect in.
 * @param iMaxLen           The lenght of string.
 **/
native void UTIL_GetEffectName(int iIndex, char[] sEffect, int iMaxLen);

/**
 * @brief Gets a string of a given index in an effect table.
 *
 * @param iIndex            The string index.
 * @param sEffect           The string to return effect in.
 * @param iMaxLen           The lenght of string.
 **/
native void UTIL_GetParticleEffectName(int iIndex, char[] sEffect, int iMaxLen);

/**
 * @brief Gets a string count in a dispatch table.
 *
 * @return                  The table size.    
 **/
native void GetEffectNameCount();

/**
 * @brief Gets a string count in an effect table.
 *
 * @return                  The table size.    
 **/
native int GetParticleEffectCount();