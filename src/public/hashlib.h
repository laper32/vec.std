#pragma once
#ifndef _VEC_STD_HASHLIB_H_
#define _VEC_STD_HASHLIB_H_

#include "hashlib/base64.h"
#include "hashlib/crc32.h"
#include "hashlib/md5.h"
#include "hashlib/sha1.h"
#include "hashlib/sha256.h"

#include "extension.h"

namespace vec
{
	namespace hashlib
	{
		sp_nativeinfo_t g_HashlibNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);

		namespace API
		{
			static cell_t MD5Sum(IPluginContext*, const cell_t*);
			static cell_t CheckCRC32(IPluginContext*, const cell_t*);
		}
	}
}

#endif // !_VEC_STD_HASHLIB_H_
