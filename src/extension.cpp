#include "extension.h"

CGlobalVars* gpGlobals = nullptr;

VECStandard g_VECStandard;

SMEXT_LINK(&g_VECStandard);

bool VECStandard::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	return SDKExtension::SDK_OnLoad(error, maxlen, late);
}

void VECStandard::SDK_OnUnload()
{
	return SDKExtension::SDK_OnUnload();
}

void VECStandard::SDK_OnAllLoaded()
{
}

bool VECStandard::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	gpGlobals = ismm->GetCGlobals();
	return SDKExtension::SDK_OnMetamodLoad(ismm, error, maxlen, late);
}
