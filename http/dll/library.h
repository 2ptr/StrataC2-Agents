#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#ifdef _WIN32
  #define DLL_EXPORT __declspec(dllexport)
#else
  #define DLL_EXPORT
#endif
#include <windows.h>

extern "C" {
    DLL_EXPORT BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
    DLL_EXPORT void RunAgent();
}

#endif // MY_LIBRARY_H