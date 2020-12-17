#pragma once

#ifndef _VEC_STD_FILEPARSER_H_
#define _VEC_STD_FILEPARSER_H_
#include "extension.h"
namespace vec
{
	namespace fileparser
	{
		namespace API
		{
			static cell_t PrecacheModel(IPluginContext*, const cell_t*);
			static cell_t PrecacheParticle(IPluginContext*, const cell_t*);
			static cell_t PrecacheWeapon(IPluginContext*, const cell_t*);
			static cell_t PrecacheSounds(IPluginContext*, const cell_t*);
			// 下面的都是功能测试, 一旦完成将会被删除.
			static cell_t PrecacheModelSounds(IPluginContext*, const cell_t*);
			static cell_t PrecacheMaterials(IPluginContext*, const cell_t*);
			static cell_t PrecacheEffects(IPluginContext*, const cell_t*);
			static cell_t PrecacheTextures(IPluginContext*, const cell_t*);
		}

		sp_nativeinfo_t g_FileParserNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);


		inline int PrecacheModel(std::string path);
		inline int PrecacheParticle(std::string path);
		inline int PrecacheWeapon(std::string path);
		inline void PrecacheResources(std::string path);
		inline bool PrecacheModelSounds(std::string path);
		inline bool PrecacheMaterials(std::string path);
		inline bool PrecacheEffects(std::string path);
		inline bool PrecacheTextures(std::string modelname, std::string path);
		inline bool PrecacheSounds(std::string path);
	}
}

#endif // !_VEC_STD_FILEPARSER_H_
