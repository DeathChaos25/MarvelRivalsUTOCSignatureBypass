// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include "config.h"

#define DEBUG 0

void* GetPakSigningKeysDelegate_Sig = sigScan(
    "\xE8\x2A\x2A\x2A\x2A\x48\x8B\xF8\x39\x70\x2A\x0F\x84\x2A\x2A\x2A\x2A",
    "x????xxxxx?xx????");

u64 GetAddressForHook()
{
    if (GetPakSigningKeysDelegate_Sig)
    {
        printf("Signature scan success\n");
        return GetAddressFromFuncCall((u64)GetPakSigningKeysDelegate_Sig);
    }
    else
    {
        printf("Signature for GetPakSigningKeysDelegate_Sig broken!\n");
        return 0;
    }
}

FPakSigningKeys* _signingKeys;

HOOK(FPakSigningKeys*, __stdcall, hook_GetPakSigningKeysDelegate, GetAddressForHook(), void)
{
    _signingKeys->Function = 0;
    _signingKeys->size = 0;
    return _signingKeys;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        if (DEBUG) // open console output
        {
            AllocConsole();
            AttachConsole(GetCurrentProcessId());
            freopen("CON", "w", stdout);
        }
        
        if (GetPakSigningKeysDelegate_Sig)
        {
            _signingKeys = (FPakSigningKeys*)malloc(sizeof(FPakSigningKeys));

            INSTALL_HOOK(hook_GetPakSigningKeysDelegate);
        }

        return TRUE;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

