#include "Anti Cheat.h"
#include <processthreadsapi.h>

HMODULE hKernel32Dll;

VOID WINAPI tls_callback(
    PVOID DllHandle,
    DWORD Reason,
    PVOID Reserved)
{
    if (Reason == DLL_PROCESS_ATTACH)
        hKernel32Dll = LoadLibrary(TEXT("Kernel32.dll"));
		pfnCreateThread CreateThread = (pfnCreateThread) GetProcAddress(hKernel32Dll, "CreateThread");

		if (NULL == CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) antiDebugger, NULL, NULL, NULL)) {

			_exit(EXIT_FAILURE);
		}
}

#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:p_tls_callback")
#pragma const_seg(push)
#pragma const_seg(".CRT$XLAAA")
    EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback = tls_callback;
#pragma const_seg(pop)