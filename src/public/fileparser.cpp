#include "fileparser.h"
#include <filesystem>
#include <string>
#include "sm/sourcemod.h"
#include <stdexcept>
#include <fstream>

namespace vec
{
	namespace fileparser
	{
		sp_nativeinfo_t g_FileParserNatives[] = {
			{"fileparser_PrecacheModel", API::PrecacheModel},
			{"fileparser_PrecacheParticle", API::PrecacheParticle},
			{"fileparser_PrecacheWeapon", API::PrecacheWeapon},
			{"fileparser_PrecacheSounds", API::PrecacheSounds},
			{"fileparser_PrecacheModelSounds", API::PrecacheModelSounds},
			{"fileparser_PrecacheMaterials", API::PrecacheMaterials},
			{"fileparser_PrecacheEffects", API::PrecacheEffects},
			{"fileparser_PrecacheTextures", API::PrecacheTextures},
			{nullptr, nullptr}
		};

		namespace API
		{
			static cell_t PrecacheModel(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheModel(path);
				return true;
			}
			static cell_t PrecacheParticle(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheParticle(path);
				return true;
			}
			static cell_t PrecacheWeapon(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheWeapon(path);
				return true;
			}
			static cell_t PrecacheSounds(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheSounds(path);
				return true;
			}
			// 下面的都是功能测试, 一旦完成将会被删除.
			static cell_t PrecacheModelSounds(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheModelSounds(path);
				return true;
			}
			static cell_t PrecacheMaterials(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheMaterials(path);
				return true;
			}
			static cell_t PrecacheEffects(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				vec::fileparser::PrecacheEffects(path);
				return true;
			}
			static cell_t PrecacheTextures(IPluginContext* pContext, const cell_t* params)
			{
				//bool PrecacheTextures(std::string modelname, std::string path)
				std::string modelname, path;
				sm::interop::cell2native(pContext, params[1], modelname);
				sm::interop::cell2native(pContext, params[2], path);
				vec::fileparser::PrecacheTextures(modelname, path);
				return true;
			}
		}
		

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_FileParserNatives);
			return true;
		}

		inline int PrecacheModel(std::string path)
		{
			if (!path.size()) return 0;

			if (!sm::filesystem::FileExists(path.c_str()))
			{
				if (sm::filesystem::FileExists(path.c_str(), true))
				{
					return sm::PrecacheModel(path.c_str(), true);
				}

				smutils->LogError(myself, "Unable to find the model: %s", path.c_str());
			}

			if (!sm::IsModelPrecached(path.c_str()))
			{
				// TODO
			}

			return sm::PrecacheModel(path.c_str(), true);
		}

		inline int PrecacheParticle(std::string path)
		{
			if (!path.size()) return 0;

			if (!sm::filesystem::FileExists(path.c_str()))
			{
				if (sm::filesystem::FileExists(path.c_str(), true))
				{
					return sm::PrecacheGeneric(path.c_str(), true);
				}

				smutils->LogError(myself, "[fileparser::PrecacheParticle] Unable to find: \"%s\"", path.c_str());
				return 0;
			}

			// If model doesn't precache yet, then continue
			/**if (!IsGenericPrecached(sFileName))**/
			// Thanks Valve!

			// Precache model effects
			PrecacheEffects(path.c_str());

			// Return the model index
			return sm::PrecacheGeneric(path.c_str(), true);
		}

		inline int PrecacheWeapon(std::string path)
		{
			return int();
		}

		/**
		 * @brief Reads the current model and precache its resources.
		 * 
		 * @note A model has '.phy', '.vvd', and . 'dx90.vtx'
		 * 
		 * @param sFileName            The model path.
		 */
		void PrecacheResources(std::string path)
		{
			sm::sdktools::AddFileToDownloadsTable(path.c_str());

			std::vector<std::string> suffix = { ".dx90.vtx", ".phy", ".vvd" };

			std::size_t first_occurence = path.rfind(".");

			if ((path.size() - first_occurence) > 4)
			{
				smutils->LogError(myself, "[fileparser::PrecacheResources] The first occurence should not > 4 (sizeof(.mdl)==4).\nFile path: \"%s\"", path.c_str());
			}

			path.erase(path.begin() + first_occurence, path.end());

			std::string resources = path;

			for (auto& i : suffix)
			{
				std::string ret = resources + i;
				if (sm::filesystem::FileExists(ret.c_str()))
				{
					sm::sdktools::AddFileToDownloadsTable(ret.c_str());
				}
			}
		}

		inline bool PrecacheModelSounds(std::string path)
		{
			std::size_t first_occurence = path.rfind('.');

			if ((path.size() - first_occurence) > 4)
			{
				smutils->LogError(myself, "[fileparser::PrecacheModelSounds] The first occurence should not > 3, because it's mp3/wav's suffix size.\nFile path: \"%s\"", path.c_str());
				return false;
			}
			
			std::string resource = path;
			resource.erase(resource.begin() + first_occurence, resource.end());
			std::string local_cache = resource + "_sounds.txt";

			bool exist = sm::filesystem::FileExists(local_cache.c_str());

			if (!exist)
			{
				sm::SystemFile* file = sm::SystemFile::Open(path.c_str(), "rb");
				std::ofstream local_fs(local_cache, std::ofstream::app);

				if (!file)
				{
					local_fs.close();
					sm::filesystem::DeleteFile(local_cache.c_str());
					smutils->LogError(myself, "[fileparser::PrecacheModelSounds] Unable to find the file: \"%s\"", path.c_str());
					return false;
				}

				int8_t iChar = 0;

				do
				{
					file->Seek(2, SEEK_CUR);
					file->Read(&iChar, sizeof(iChar));
				} while (!iChar);

				file->Seek(1, SEEK_CUR);

				do
				{
					file->Seek(2, SEEK_CUR);
					file->Read(&iChar, sizeof(iChar));
				} while (iChar);

				char temp[256];
				while (!file->EndOfFile())
				{
					sm::ReadFileString(file, temp, sizeof(temp));

					if (std::strstr(temp, ".mp3") || std::strstr(temp, ".wav"))
					{
						std::string out = std::string("sounds/") + std::string(temp) + "\n";
						local_fs.write(out.c_str(), out.size());

						vec::fileparser::PrecacheSounds(out);
					}
				}

				local_fs.close();
				delete file;
			}
			else
			{
				std::ifstream local_fs(local_cache);
				std::string lines;

				while (std::getline(local_fs, lines))
				{
					if (lines.rfind("//") != std::string::npos) lines.erase(lines.begin() + lines.rfind("//"), lines.end());
					std::remove_if(lines.begin(), lines.end(), isspace);

					if (!lines.size()) continue;

					vec::fileparser::PrecacheSounds(lines);
				}
				local_fs.close();
			}

			return true;
		}

		bool PrecacheMaterials(std::string path)
		{
			std::size_t first_occurence = path.rfind('.');
			if (path.size() - first_occurence > 4)
			{
				smutils->LogError(myself, "[fileparser::PrecacheEffects] The first occurence should not > 4, because it's vmt's suffix size.\nFile path: \"%s\"", path.c_str());
				return false;
			}

			std::string resource = path;
			resource.erase(resource.begin() + first_occurence, resource.end());
			std::string local_cache = resource + "_materials.txt";

			bool exist = sm::filesystem::FileExists(local_cache.c_str());

			if (!exist)
			{
				sm::SystemFile* file = sm::SystemFile::Open(path.c_str(), "rb");
				std::ofstream local_fs(local_cache, std::ofstream::app);

				if (!file)
				{
					local_fs.close();
					sm::filesystem::DeleteFile(local_cache.c_str());
					smutils->LogError(myself, "Unable to find the file: \"%s\"", path.c_str());
					return false;
				}

				char sMaterial[256] = {}; int32_t iNumMat = 0; int8_t iChar = 0;

				file->Seek(204, SEEK_SET);
				file->Read(&iNumMat, sizeof(iNumMat));
				file->Seek(0, SEEK_END);

				do
				{
					file->Seek(2, SEEK_CUR);
					file->Read(&iChar, sizeof(iChar));
				} while (!iChar);

				file->Seek(1, SEEK_CUR);

				do
				{
					file->Seek(2, SEEK_CUR);
					file->Read(&iChar, sizeof(iChar));
				} while (iChar);

				int iPosIndex = file->Tell();
				sm::ReadFileString(file, sMaterial, sizeof(sMaterial));
				file->Seek(iPosIndex, SEEK_SET);
				file->Seek(-1, SEEK_CUR);

				std::vector<std::string> hList;

				char sTemp[256] = {};
				while (file->Tell() > 1 && hList.size() < iNumMat)
				{
					do
					{
						file->Seek(-2, SEEK_CUR);
						file->Read(&iChar, sizeof(iChar));
					} while (iChar);

					iPosIndex = file->Tell();
					sm::ReadFileString(file, sTemp, sizeof(sTemp));
					file->Seek(iPosIndex, SEEK_SET);
					file->Seek(-1, SEEK_CUR);
					
					std::string sMaterialPath(sTemp);
					if (!sMaterialPath.size()) continue;

					if (sMaterialPath.rfind('.'))
					{
						sMaterialPath = "materials\\" + sMaterialPath;
					}
				}
			}
			else
			{

			}

			return bool();
		}
		
		bool PrecacheEffects(std::string path)
		{
			std::size_t first_occurence = path.rfind('.');
			if (path.size() - first_occurence > 4)
			{
				smutils->LogError(myself, "[fileparser::PrecacheEffects] The first occurence should not > 4, because it's vmt's suffix size.\nFile path: \"%s\"", path.c_str());
				return false;
			}

			std::string resource = path;
			resource.erase(resource.begin() + first_occurence, resource.end());
			std::string local_cache = resource + "_particles.txt";

			bool exist = sm::filesystem::FileExists(local_cache.c_str());

			if (!exist)
			{
				sm::SystemFile* file = sm::SystemFile::Open(path.c_str(), "rb");
				std::ofstream local_fs(local_cache, std::ofstream::app);

				if (!file)
				{
					local_fs.close();
					sm::filesystem::DeleteFile(local_cache.c_str());
					smutils->LogError(myself, "Unable to find the file: \"%s\"", path.c_str());
					return false;
				}

				int8_t iChar = 0;

				do
				{
					file->Seek(2, SEEK_CUR);
					file->Read(&iChar, sizeof(iChar));
				} while (!iChar);

				file->Seek(1, SEEK_CUR);

				do
				{
					file->Seek(2, SEEK_CUR);
					file->Read(&iChar, sizeof(iChar));
				} while (iChar);

				char temp[256] = {};
				while (!file->EndOfFile())
				{
					sm::ReadFileString(file, temp, sizeof(temp));

					if (std::strstr(temp, ".vmt"))
					{
						std::string out = std::string("materials\\") + std::string(temp) + "\n";
						local_fs.write(out.c_str(), out.size());

						PrecacheTextures(path, out);
					}
				}

				local_fs.close();
				file->Close();
				delete file;
			}
			else
			{
				std::ifstream local_fs(local_cache);
				std::string lines;

				while (std::getline(local_fs, lines))
				{
					if (lines.rfind("//") != std::string::npos) lines.erase(lines.begin() + lines.rfind("//"), lines.end());
					std::remove_if(lines.begin(), lines.end(), isspace);

					if (!lines.size()) continue;
					PrecacheTextures(path, lines);
				}
				local_fs.close();
			}

			return true;
		}

		bool PrecacheTextures(std::string modelname, std::string path)
		{
			int iSlash = std::max<int>(modelname.rfind('/'), modelname.rfind('\\'));
			if (iSlash == -1) iSlash = 0; else iSlash++;
			modelname.erase(modelname.begin(), modelname.begin() + iSlash);

			std::string sTexture = path;

			if (!sm::filesystem::FileExists(sTexture.c_str()))
			{
				if (sm::filesystem::FileExists(sTexture.c_str(), true))
				{
					return true;
				}
				
				smutils->LogError(myself, "[fileparser::PrecacheTextures] Invalid material path. File not found: \"%s\" in \"%s\"", sTexture.c_str(), modelname);
				return false;
			}

			//sm::sdktools::AddFileToDownloadsTable(sTexture.c_str());

			std::vector<std::string> sTypes = { "$baseTexture", "$bumpmap", "$lightwarptexture", "$REFRACTTINTtexture" };

			std::vector<bool> bFound(sTypes.size(), false);
			int iShift = 0;

			char temp[256];
			g_pSM->BuildPath(Path_Game, temp, sizeof(temp), "%s", sTexture.c_str());
			std::ifstream in(temp);

			if (in.bad())
			{
				smutils->LogError(myself, "[fileparser::PrecacheTexture] Error opening file: %s", temp);
				return false;
			}

			int cnt = 0;

			while (std::getline(in, sTexture))
			{
				if (sTexture.find("//") != std::string::npos) sTexture.erase(sTexture.begin() + sTexture.rfind("//"), sTexture.end());
				for (std::size_t i = 0; i < sTypes.size(); i++)
				{
					if (bFound[i]) continue;
					
					if ((iShift = sm::StrContains(sTexture, sTypes[i])) != -1)
					{
						iShift += sTypes[i].size() + 1;

						std::size_t iQuotes = std::count(sTexture.begin() + iShift, sTexture.end(), '"');
						if (iQuotes != 2)
						{
							smutils->LogError(myself, "Error with parsing \"%s\" in file: \"%s\"", sTypes[i].c_str(), path.c_str());
							return false;
						}
						else
						{
							bFound[i] = true;

							sTexture.replace(sTexture.begin(), sTexture.begin() + iShift, "");

							sTexture.erase(std::remove(sTexture.begin(), sTexture.end(), '\"'), sTexture.end());

							sTexture.erase(std::remove_if(sTexture.begin(), sTexture.end(), isspace), sTexture.end());

							if (!sTexture.size()) continue;

							sTexture = "materials\\" + sTexture + ".vtf";
							std::replace(sTexture.begin(), sTexture.end(), '/', '\\');

							if (sm::filesystem::FileExists(sTexture.c_str()))
							{

								sm::sdktools::AddFileToDownloadsTable(sTexture.c_str());
							}
							else
							{
								if (!sm::filesystem::FileExists(sTexture.c_str()))
								{
									smutils->LogError(myself, "[fileparser::PrecacheTextures] Invalid texture path. File not found: \"%s\" in \"%s\"", sTexture.c_str(), modelname);
								}
							}
						}
					}
				}
			}

			return true;
		}

		/**
		 * @brief Precache the sound in the sounds table.
		 *
		 * @param sPath             The sound path.
		 * @return                  True if was precached, false otherwise.
		 **/
		inline bool PrecacheSounds(std::string path)
		{
			if (!sm::filesystem::FileExists(path.c_str()))
			{
				if (sm::filesystem::FileExists(path.c_str(), true))
				{
					sm::PrecacheSound(path.c_str(), true);
					return true;
				}

				smutils->LogError(myself, "[fileparser::PrecacheSounds] Invalid sound path. File not found: \"%s\"", path.c_str());
				return false;
			}

			std::string sSound(path);

			if (sSound.find("sound", 5))
			{
				sSound.replace(sSound.begin(), sSound.begin() + 5, 1, '*');

				// Initialize the table index
				int table = INVALID_STRING_TABLE;

				// if is -1, search for a string table.
				if (table == INVALID_STRING_TABLE) table = sm::sdktools::FindStringTable("soundprecache");

				if (sm::sdktools::FindStringIndex(table, sSound) == INVALID_STRING_INDEX)
				{
					sm::sdktools::AddFileToDownloadsTable(path.c_str());

					//bool bSave = sm::sdktools::LockStringTables(false);
					sm::sdktools::AddToStringTable(table, sSound.c_str());
					//sm::sdktools::LockStringTables(bSave);
				}
			}
			else
			{
				smutils->LogError(myself, "[fileparser::PrecacheSounds] Invalid sound path, file not found: \"%s\"", path);
				return false;
			}

			return true;
		}
	}
}