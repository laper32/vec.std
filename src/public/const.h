#pragma once

enum ExplosionFlags
{
	EXP_NODAMAGE			= (1<<0),
	EXP_REPEATABLE			= (1<<1),
	EXP_NOFIREBALL			= (1<<2),
	EXP_NOSMOKE				= (1<<3),
	EXP_NODECAL				= (1<<4),
	EXP_NOSPARKS			= (1<<5),
	EXP_NOSOUND				= (1<<6),
	EXP_RANDOMORIENTATION	= (1<<7),
	EXP_NOFIREBALLSMOKE		= (1<<8),
	EXP_NOPARTICLES			= (1<<9),
	EXP_NODLIGHTS			= (1<<10),
	EXP_NOCLAMPMIN			= (1<<11),
	EXP_NOCLAMPMAX			= (1<<12),
	EXP_NOUNDERWATER		= (1<<13),
	EXP_GENERICDAMAGE		= (1<<14)
};

enum RenderColorType_t : int
{
	Color_Red,
	Color_Green,
	Color_Blue,
	Color_Alpha
};

enum HideHUDElementFlags_t
{
	HideHUD_WeaponSelection			= (1<<0),	/// Hide ammo count & weapon selection
	HideHUD_FlashLight				= (1<<1),
	HideHUD_All						= (1<<2),
	HideHUD_Health					= (1<<3),	/// Hide health & armor / suit battery
	HideHUD_PlayerDead				= (1<<4),	/// Hide when local player's dead
	HideHUD_NeedSuit				= (1<<5),	/// Hide when the local player doesn't have the HEV suit
	HideHud_MiscStatus				= (1<<6),	/// Hide miscellaneous status elements (trains, pickup history, death notices, etc)
	HideHUD_Chat					= (1<<7),	/// Hide all communication elements (saytext, voice icon, etc)
	HideHUD_Crosshair				= (1<<8),	/// Hide crosshairs
	HideHUD_Vehicle_Crosshair		= (1<<9),	/// Hide vehicle crosshair
	HideHUD_Invehicle				= (1<<10),
	HideHUD_Bonus_Progress			= (1<<11),	/// Hide bonus progress display (for bonus map challenges)
	HideHUD_Radar					= (1<<12)
};