#include "stdafx.h"
#include "winmanager.h"
using namespace std;
using namespace win;

string winManager::gettitle() {
	HWND handle = GetForegroundWindow();
	DWORD err = GetLastError();
	char buffer[255] = { 0, };
	GetWindowTextA(handle, buffer, sizeof(buffer));
	return buffer;
}