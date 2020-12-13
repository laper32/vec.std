#include "hashlib.h"
#include <fstream>
namespace vec
{
	namespace hashlib
	{
		sp_nativeinfo_t g_HashlibNatives[] = {
			{"md5sum", API::MD5Sum},
			{"checkcrc32", API::CheckCRC32},
			{nullptr, nullptr}
		};

		namespace API
		{
			static cell_t MD5Sum(IPluginContext* pContext, const cell_t* params)
			{
				char* input;
				pContext->LocalToString(params[1], &input); // InputVal

				int status = false;

				bool isFile = params[4];
				if (isFile)
				{
					char* memblock;
					char filepath[PLATFORM_MAX_PATH + 1];

					vec::hashlib::MD5 md5;

					g_pSM->BuildPath(Path_Game, filepath, sizeof(filepath), input);
					std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
					if (file.bad() || !file.is_open())
					{
						pContext->ReportError("Unable to open the file: %s", filepath);
						status = false;
					}

					int size = (int)file.tellg();
					if (size < 1)
					{
						status = pContext->StringToLocalUTF8(params[2], params[3], "", nullptr);
						g_SMAPI->ConPrintf("Warning: The file size is empty: \"%s\", are you sure that this file what you have input is a vaild file?", filepath);
					}

					memblock = new char[size];


					file.seekg(0, std::ios::beg);
					file.read(memblock, size);
					file.close();

					md5.add(memblock, size);

					delete[] memblock;

					status = pContext->StringToLocalUTF8(params[2], params[3], md5.getHash().c_str(), nullptr);
				}
				else
				{
					if (!std::strlen(input))
					{
						g_SMAPI->ConPrint("Warning: The string what you have input is empty.");
						status = pContext->StringToLocalUTF8(params[2], params[3], "", nullptr);
					}

					vec::hashlib::MD5 md5;

					std::string output = md5(std::string(input));
					
					status = pContext->StringToLocalUTF8(params[2], params[3], output.c_str(), nullptr);
				}

				return status;
			}
			static cell_t CheckCRC32(IPluginContext* pContext, const cell_t* params)
			{
				char* memblock;
				char* filePath;
				char fullFilePath[PLATFORM_MAX_PATH + 1];

				// Get the full paths to the file
				pContext->LocalToString(params[1], &filePath);
				g_pSM->BuildPath(Path_Game, fullFilePath, sizeof(fullFilePath), filePath);

				// Open the file
				std::ifstream file(fullFilePath, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
				if (file.bad() || !file.is_open())
				{
					pContext->ReportError("Unable to open the file: %s", filePath);
					return false;
				}

				// Get the size of the file and save the content to a var
				int size = (int)file.tellg();
				if (size < 1)
				{
					pContext->StringToLocalUTF8(params[2], params[3], "", nullptr);
					g_SMAPI->ConPrintf("Warning: The file size is empty: \"%s\", are you sure that this file what you have input is a vaild file?", filePath);
					return false;
				}

				memblock = new char[size];
				file.seekg(0, std::ios::beg);
				file.read(memblock, size);
				file.close();

				// Calculate the CRC32 hash
				char crc32[9];
				vec::hashlib::crc32::toHex(vec::hashlib::crc32::buf(memblock, size), crc32, sizeof(crc32));

				// Free the memory from reading again
				delete[] memblock;

				// Save the CRC32 hash to the plugins buffer
				return pContext->StringToLocalUTF8(params[2], params[3], crc32, nullptr);
			}
		}

		bool SDK_OnLoad(char* error, size_t maxlen, bool late)
		{
			sharesys->AddNatives(myself, g_HashlibNatives);
			return true;
		}
	}
}