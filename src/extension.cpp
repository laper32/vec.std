/*
./src
	- extension.h
	- extension.cpp
	- functions.h
	- functions.cpp

	./public
		- ...

*/

#include "extension.h"

#include "filesystem.h"

#include "sm/sourcemod.h"

#include "functions.h"

CGlobalVars* gpGlobals = nullptr;

VECStandard g_VECStandard;

SMEXT_LINK(&g_VECStandard);

bool VECStandard::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	sm::SDK_OnLoad(error, maxlen, late);
	vec::functions::SDK_OnLoad(error, maxlen, late);
	return SDKExtension::SDK_OnLoad(error, maxlen, late);
}

void VECStandard::SDK_OnUnload()
{
	sm::SDK_OnUnload();
	return SDKExtension::SDK_OnUnload();
}

void VECStandard::SDK_OnAllLoaded()
{
	
}

bool VECStandard::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	gpGlobals = ismm->GetCGlobals();
	sm::SDK_OnMetamodLoad(ismm, error, maxlen, late);
	return SDKExtension::SDK_OnMetamodLoad(ismm, error, maxlen, late);
}
