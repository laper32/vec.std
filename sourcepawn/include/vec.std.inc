#if defined _vec_std_included
#endinput
#endif

#define _vec_std_included

#define inline stock

#if !defined _sourcemod_included
#include <sourcemod>
#endif

#if !defined _sdktools_included
#include <sdktools>
#endif

#if !defined _sdkhooks_included
#include <sdkhooks>
#endif

#if !defined _cstrike_included
#include <cstrike>
#endif

#if !defined _ptah_included
#include <ptah>
#endif

#if !defined _dhooks_included
#include <dhooks>
#endif

#include <vec.std/const>
#include <vec.std/engine>
#include <vec.std/math>
#include <vec.std/mem>
#include <vec.std/paramparser>
#include <vec.std/fileparser>
#include <vec.std/tools>
#include <vec.std/utils>
#include <vec.std/text>
#include <vec.std/playermgr>
#include <vec.std/hint>
#include <vec.std/hashlib>

// std
// all of these functions what we used are required.
// so it's unncessary to write MarkNativeAsOptional.
public Extension __ext_vec_std =
{
	name = "Vector community - Standard",
	file = "vec.std.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

// stdlib
// all of these functions what we used are required.
// so it's unncessary to write MarkNativeAsOptional.
public SharedPlugin _sp_vec_stdlib = 
{
	name = "Vector community - Standard library",
	file = "vec.stdlib.smx",
#if defined REQUIRE_PLUGIN
    required = 1
#else
    required = 0
#endif
}