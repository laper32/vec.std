#include "fileparser.h"
#include <filesystem>
#include <string>
#include "sm/sourcemod.h"
#include <stdexcept>
#include <fstream>

/*
TODO
1. 重写文件安全检查逻辑.
2. 为变量设置正确的命名.
3. 优化
*/

namespace vec
{
	namespace fileparser
	{
		sp_nativeinfo_t g_FileParserNatives[] = {
			{"fileparser_PrecacheModel", API::PrecacheModel},
			{"fileparser_PrecacheParticle", API::PrecacheParticle},
			{"fileparser_PrecacheWeapon", API::PrecacheWeapon},
			{"fileparser_PrecacheSounds", API::PrecacheSounds},
			{nullptr, nullptr}
		};

		namespace API
		{
			static cell_t PrecacheModel(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				return vec::fileparser::PrecacheModel(path);;
			}
			static cell_t PrecacheParticle(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				return vec::fileparser::PrecacheParticle(path);;
			}
			static cell_t PrecacheWeapon(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				return vec::fileparser::PrecacheWeapon(path);;
			}
			static cell_t PrecacheSounds(IPluginContext* pContext, const cell_t* params)
			{
				std::string path;
				sm::interop::cell2native(pContext, params[1], path);
				return vec::fileparser::PrecacheSounds(path);;
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
				return 0;
			}

			if (!sm::IsModelPrecached(path.c_str()))
			{
				PrecacheMaterials(path);

				PrecacheResources(path);
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
			if (!path.size()) return 0;

			if (!sm::filesystem::FileExists(path.c_str()))
			{
				if (sm::filesystem::FileExists(path.c_str(), true))
				{
					return sm::PrecacheModel(path.c_str(), true);
				}

				smutils->LogError(myself, "[fileparser::PrecacheWeapon] Unable to find: \"%s\"", path.c_str());
				return 0;
			}

			if (!sm::IsModelPrecached(path.c_str()))
			{
				PrecacheModelSounds(path);

				PrecacheMaterials(path);

				PrecacheResources(path);
			}

			return sm::PrecacheModel(path.c_str(), true);
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
			int iFormat = sm::FindCharInString(path, path.rfind('.'));

			if (iFormat == -1)
			{
				smutils->LogError(myself, "[fileparser::PrecacheModelSounds] Missing file format: %s", path.c_str());
				return false;
			}

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

				char cache_realpath[256];
				g_pSM->BuildPath(Path_Game, cache_realpath, sizeof(cache_realpath), "%s", local_cache.c_str());
				std::ofstream local_fs(cache_realpath, std::ofstream::app);

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
						std::string out = std::string("sound/") + std::string(temp);
						std::replace(out.begin(), out.end(), '\\', '/');
						local_fs.write(std::string(out + "\n").c_str(), std::string(out + "\n").size());

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

		inline bool PrecacheMaterials(std::string sFileName)
		{
			int iFormat = sm::FindCharInString(sFileName, sFileName.rfind('.'));

			if (iFormat == -1)
			{
				smutils->LogError(myself, "[fileparser::PrecacheMaterials] Missing file format: %s", sFileName.c_str());
				return false;
			}

			std::size_t iFirstOccurence = sFileName.rfind('.');

			if (sFileName.size() - iFirstOccurence > 4)
			{
				smutils->LogError(myself, "[fileparser::PrecacheMaterials] The first occurence should not > 4, because it's vmt's suffix size.\nFile path: \"%s\"", sFileName.c_str());
				return false;
			}

			std::string sPath = sFileName;
			sPath.erase(sPath.begin() + iFirstOccurence, sPath.end());

			sPath += "_materials.txt";

			char sRealLocalCache[256] = {};
			g_pSM->BuildPath(Path_Game, sRealLocalCache, sizeof(sRealLocalCache), "%s", sPath.c_str());

			bool bExist = sm::FileExists(sPath.c_str());

			if (!bExist)
			{
				sm::SystemFile* pFile = sm::SystemFile::Open(sFileName.c_str(), "rb");

				char sRealLocalCache[256] = {};
				g_pSM->BuildPath(Path_Game, sRealLocalCache, sizeof(sRealLocalCache), "%s", sPath.c_str());
				std::ofstream local_fs(sRealLocalCache, std::ofstream::app);

				if (!pFile)
				{
					local_fs.close();
					sm::DeleteFile(sPath.c_str());

					smutils->LogError(myself, "Unable to find the file: \"%s\"", sFileName.c_str());
					return false;
				}

				char sMaterial[256]; int iNumMat; int8_t iChar;

				pFile->Seek(204, SEEK_SET);
				pFile->Read(&iNumMat, sizeof(iNumMat));
				pFile->Seek(0, SEEK_END);

				do
				{
					pFile->Seek(-2, SEEK_CUR);
					pFile->Read(&iChar, sizeof(iChar));
				} while (!iChar);

				pFile->Seek(-1, SEEK_CUR);

				do
				{
					pFile->Seek(-2, SEEK_CUR);
					pFile->Read(&iChar, sizeof(iChar));
				} while (iChar);

				int iPosIndex = pFile->Tell();
				sm::ReadFileString(pFile, sMaterial, sizeof(sMaterial));
				pFile->Seek(iPosIndex, SEEK_SET);
				pFile->Seek(-1, SEEK_CUR);

				std::vector<std::string> vList;

				char sPathTemp[256];
				while (pFile->Tell() > 1 && vList.size() < iNumMat)
				{
					do
					{
						pFile->Seek(-2, SEEK_CUR);
						pFile->Read(&iChar, sizeof(iChar));
					} while (iChar);

					iPosIndex = pFile->Tell();
					sm::ReadFileString(pFile, sPathTemp, sizeof(sPathTemp));
					pFile->Seek(iPosIndex, SEEK_SET);
					pFile->Seek(-1, SEEK_CUR);
					
					if (sPathTemp[0] == '\0') continue;

					sPath = sPathTemp;
					if (!sPath.size()) continue;

					iFormat = sm::FindCharInString(sPath, sPath.rfind('\\'));

					if (iFormat != -1)
					{
						sPath = std::string("materials\\") + sPath;

						g_pSM->BuildPath(Path_Game, sPathTemp, sizeof(sPathTemp), "%s", sPath.c_str());

						std::unique_ptr<IDirectory> pDir(libsys->OpenDirectory(sPathTemp));

						if (!pDir)
						{
							smutils->LogError(myself, "[fileparser::PrecacheMaterials] Error opening folder: %s", sPath.c_str());
							//META_CONPRINTF("pDir is nullptr. With: %s\n", sPath.c_str());
							continue;
						}

						while (pDir->MoreFiles())
						{
							if (pDir->IsEntryFile())
							{
								std::string sFile = std::string(pDir->GetEntryName());
								
								iFormat = sm::FindCharInString(sFile, sFile.rfind('.'));

								if (iFormat != -1)
								{
									if (std::equal(sFile.rbegin(), sFile.rbegin() + 4, std::string(".vmt").rbegin(), [](char a, char b) {return tolower(a) == tolower(b); }))
									{										
										if (std::find(vList.begin(), vList.end(), sFile) == vList.end())
										{
											vList.push_back(sFile);
										}

										sFile = sPath + sFile;

										local_fs.write(std::string(sFile + "\n").c_str(), std::string(sFile + "\n").size());

										PrecacheTextures(sFileName, sFile);
									}
								}
							}

							pDir->NextEntry();
						}
					}
					else
					{
						sPath += ".vmt";
						if (std::find(vList.begin(), vList.end(), sPath) == vList.end())
						{
							vList.push_back(sPath);
						}

						sPath = std::string("materials\\") + std::string(sMaterial) + sPath;
						local_fs.write(std::string(sPath + "\n").c_str(), std::string(sPath + "\n").size());

						PrecacheTextures(sFileName, sPath);
					}
				}

				local_fs.close();
				pFile->Close();
				delete pFile;
			}
			else
			{
				std::ifstream local_fs(sRealLocalCache);
				std::string lines;
				while (std::getline(local_fs, lines))
				{
					if (lines.rfind("//") != std::string::npos) lines.erase(lines.begin() + lines.rfind("//"), lines.end());
					std::remove_if(lines.begin(), lines.end(), isspace);

					if (!lines.size()) continue;
					PrecacheTextures(sFileName, lines);
				}
				local_fs.close();

			}
			return true;
		}
		
		inline bool PrecacheEffects(std::string path)
		{
			int iFormat = sm::FindCharInString(path, path.rfind('.'));
			if (iFormat == -1)
			{
				smutils->LogError(myself, "[fileparser::PrecacheEffects] Missing file format: %s", path.c_str());
				return false;
			}

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
			
			char localCacheRealPath[256];
			g_pSM->BuildPath(Path_Game, localCacheRealPath, sizeof(localCacheRealPath), "%s", local_cache.c_str());

			if (!exist)
			{
				sm::SystemFile* file = sm::SystemFile::Open(path.c_str(), "rb");
				std::ofstream local_fs(localCacheRealPath, std::ofstream::app);

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
						std::string out = std::string("materials\\") + std::string(temp);
						
						local_fs.write(std::string(out + "\n").c_str(), std::string(out + "\n").size());

						PrecacheTextures(path, out);
					}
				}

				local_fs.close();
				file->Close();
				delete file;
			}
			else
			{
				std::ifstream local_fs(localCacheRealPath);
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

				smutils->LogError(myself, "[fileparser::PrecacheTextures] Unable to find file: \"%s\" in \"%s\"", sTexture.c_str(), modelname.c_str());
				return false;
			}

			sm::sdktools::AddFileToDownloadsTable(sTexture.c_str());

			std::vector<std::string> sTypes = { "$baseTexture", "$bumpmap", "$lightwarptexture", "$REFRACTTINTtexture" };

			std::vector<bool> bFound(sTypes.size(), false);
			int iShift = 0;

			char temp[256];
			g_pSM->BuildPath(Path_Game, temp, sizeof(temp), "%s", sTexture.c_str());
			std::ifstream in(temp);

			if (in.bad())
			{
				smutils->LogError(myself, "[fileparser::PrecacheTextures] Error opening file: %s", temp);
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

							sTexture.erase(sTexture.begin(), sTexture.begin() + iShift);

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