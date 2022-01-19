#include "Anti Cheat.h"

void antiDebugger() {

	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
    pfnNtSetInformationThread NtSetInformationThread = (pfnNtSetInformationThread) GetProcAddress(hNtDll, "NtSetInformationThread");

	if (STATUS_SUCCESS == NtSetInformationThread(NtCurrentThread, ThreadHideFromDebugger, NULL, 0)) {

		WCHAR* outputString = L"fnkjln;;";
		const ULONG_PTR lpArguments[2] = {(ULONG_PTR) wcslen(outputString) + 1, (ULONG_PTR) outputString};

		while (TRUE) {
		
			BOOL isDebugged = TRUE;

			__try {

				RaiseException(DBG_PRINTEXCEPTION_WIDE_C, EXCEPTION_CONTINUABLE, sizeof(lpArguments)/sizeof(lpArguments[0]), lpArguments);
			} __except (EXCEPTION_EXECUTE_HANDLER) {
				
				isDebugged = FALSE;
			}

			if (isDebugged) {

				break;
			}
		}
	}
	
	_exit(EXIT_FAILURE);
}