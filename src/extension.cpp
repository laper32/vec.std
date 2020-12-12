/*
* majority convert https://github.com/laper32/laper32
* my own include to community standard.
./src
	- extension.h
	- extension.cpp
	- functions.h
	- functions.cpp

	./public
		- ...

*/

#include "extension.h"

#include "sm/sourcemod.h"
#include "sm/coro.h"
#include "functions.h"

CGlobalVars* gpGlobals = nullptr;
KeyValues* kv = nullptr;

VECStandard g_VECStandard;

SMEXT_LINK(&g_VECStandard);

#include <random>
#include <filesystem>

static const char* g_DebugHintMessage[] = {
	"���ǵ� 1 ��������Ϣ",
	"���ǵ� 2 ��������Ϣ",
	"���ǵ� 3 ��������Ϣ",
	"���ǵ� 4 ��������Ϣ",
	"���ǵ� 5 ��������Ϣ",
	"���ǵ� 6 ��������Ϣ"
};

#ifdef _WIN32
inline std::string ConvertGBKToUTF8(const std::string& strGbk)//�����strGbk��GBK����  
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

// UTF8תGBK
inline std::string ConvertUTF8ToGBK(const std::string& strUtf8)
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
// TODO
inline std::string GBK_To_UTF8(const std::string& strGbk)
{
	iconv_t conv;
	conv = iconv_open("utf-8", "gb2312");
	std::unique_ptr<char_t[]> strUnicode(new wchar_t[strGbk.size() + 1]{}); //len=2
	iconv(...);
	iconv_close(conv);
	return strGbk;
}

// TODO
inline std::string UTF8_To_GBK(const std::string& strUtf8)
{
	return strUtf8;
}
#endif

namespace debug
{
	static std::shared_ptr<ITimer> g_DebugHint;
	void SendDebugMessage()
	{
		sm::PrintToChatAllStr("RequestFrameBuffer");
	}

	void SendMessageWithFrame()
	{
		sm::RequestFrame(SendDebugMessage);
	}

	sm::coro::Task Co_DebugHint()
	{
		std::random_device rd;
		std::uniform_int_distribution<std::size_t> rg(0, std::extent<decltype(g_DebugHintMessage)>::value - 1);
		while (1)
		{
			co_await sm::coro::CreateTimer(std::uniform_real_distribution<float>(15, 30)(rd));
			sm::PrintToChatAllStr(ConvertGBKToUTF8(std::string(g_DebugHintMessage[rg(rd)])));
			SendMessageWithFrame();
		}
	}
}

bool VECStandard::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	sm::SDK_OnLoad(error, maxlen, late);
	vec::functions::SDK_OnLoad(error, maxlen, late);
	sharesys->RegisterLibrary(myself, "vec.std");
	debug::Co_DebugHint();

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
