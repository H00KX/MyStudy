// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>

using doFun = void(*)();
void fun() {
	MessageBoxA(NULL, "注入成功", "提示", MB_OK);
	auto handle = GetModuleHandle(L"ntdll.dll");
	auto addr = GetProcAddress(handle, "DbgBreakPoint");
	(doFun)addr();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		fun();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

