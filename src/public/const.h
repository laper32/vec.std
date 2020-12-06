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
	Color_Grren,
	Color_Blue,
	Color_Alpha
};