#include <Windows.h>
#include <libloaderapi.h>
#include <winternl.h>
#include <errhandlingapi.h>
#include <cstdlib>

#define DBG_PRINTEXCEPTION_WIDE_C 0x4001000A
#define EXCEPTION_CONTINUABLE 0
#define NtCurrentThread (((HANDLE)(LONG_PTR)-2))
#define ThreadHideFromDebugger ((ULONG) 0x00000011)
#define STATUS_SUCCESS ((NTSTATUS) 0x00000000L)

typedef NTSTATUS (NTAPI *pfnNtSetInformationThread)(
    _In_ HANDLE ThreadHandle,
    _In_ ULONG  ThreadInformationClass,
    _In_ PVOID  ThreadInformation,
    _In_ ULONG  ThreadInformationLength
    );

typedef HANDLE (WINAPI *pfnCreateThread) (
    _In_    LPSECURITY_ATTRIBUTES   lpThreadAttributes,
    _In_    SIZE_T                  dwStackSize,
    _In_    LPTHREAD_START_ROUTINE  lpStartAddress,
    _In_    LPVOID                  lpParameter,
    _In_    DWORD                   dwCreationFlags,
    _Out_   LPDWORD                 lpThreadId
);

void antiDebugger();