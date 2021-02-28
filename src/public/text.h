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
			//gbkתunicode  
			auto len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
			std::unique_ptr<wchar_t[]> strUnicode(new wchar_t[len + 1]{});
			MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode.get(), len);

			//unicodeתUTF-8  
			len = WideCharToMultiByte(CP_UTF8, 0, strUnicode.get(), -1, NULL, 0, NULL, NULL);
			std::unique_ptr<char[]> strUtf8(new char[len + 1]{});
			WideCharToMultiByte(CP_UTF8, 0, strUnicode.get(), -1, strUtf8.get(), len, NULL, NULL);

			//��ʱ��strUtf8��UTF-8����  
			return std::string(strUtf8.get());
		}
		inline std::string TransformFromUTF8ToGBK(const std::string& strUtf8)
		{
			//UTF-8תunicode  
			int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
			std::unique_ptr<wchar_t[]> strUnicode(new wchar_t[len + 1]{});//len = 2  
			MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, strUnicode.get(), len);

			//unicodeתgbk  
			len = WideCharToMultiByte(CP_ACP, 0, strUnicode.get(), -1, NULL, 0, NULL, NULL);
			std::unique_ptr<char[]>strGbk(new char[len + 1]{});//len=3 ����Ϊ2������char*�����Զ�������\0  
			WideCharToMultiByte(CP_ACP, 0, strUnicode.get(), -1, strGbk.get(), len, NULL, NULL);

			//��ʱ��strTemp��GBK����  
			return std::string(strGbk.get());
	}
#else
		inline std::string TransformFromGBKToUTF8(const std::string& strGbk);
		inline std::string TransformFromUTF8ToGBK(const std::string& stdUTF8);
#endif
	}
}