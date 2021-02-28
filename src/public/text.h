#pragma once

#include <string>

namespace vec
{
	namespace text
	{
		sp_nativeinfo_t g_TextNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);
		namespace API
		{
			static cell_t TransformFromGBKToUTF8(IPluginContext* pContext, const cell_t* params);
			static cell_t TransformFromUTF8ToGBK(IPluginContext* pContext, const cell_t* params);
		}

#ifdef _WIN32
		

		// encoding with GBK
		inline std::string TransformFromGBKToUTF8(const std::string& strGbk)
		{
			//gbk转unicode  
			auto len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
			std::unique_ptr<wchar_t[]> strUnicode(new wchar_t[len + 1]{});
			MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode.get(), len);

			//unicode转UTF-8  
			len = WideCharToMultiByte(CP_UTF8, 0, strUnicode.get(), -1, NULL, 0, NULL, NULL);
			std::unique_ptr<char[]> strUtf8(new char[len + 1]{});
			WideCharToMultiByte(CP_UTF8, 0, strUnicode.get(), -1, strUtf8.get(), len, NULL, NULL);

			//此时的strUtf8是UTF-8编码  
			return std::string(strUtf8.get());
		}
		inline std::string TransformFromUTF8ToGBK(const std::string& strUtf8)
		{
			//UTF-8转unicode  
			int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
			std::unique_ptr<wchar_t[]> strUnicode(new wchar_t[len + 1]{});//len = 2  
			MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, strUnicode.get(), len);

			//unicode转gbk  
			len = WideCharToMultiByte(CP_ACP, 0, strUnicode.get(), -1, NULL, 0, NULL, NULL);
			std::unique_ptr<char[]>strGbk(new char[len + 1]{});//len=3 本来为2，但是char*后面自动加上了\0  
			WideCharToMultiByte(CP_ACP, 0, strUnicode.get(), -1, strGbk.get(), len, NULL, NULL);

			//此时的strTemp是GBK编码  
			return std::string(strGbk.get());
	}
#else
		inline std::string TransformFromGBKToUTF8(const std::string& strGbk);
		inline std::string TransformFromUTF8ToGBK(const std::string& stdUTF8);
#endif
	}
}