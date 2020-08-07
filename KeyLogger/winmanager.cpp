#include "stdafx.h"
using namespace std;

string gettitle() {
	HWND handle = GetForegroundWindow();
	DWORD err = GetLastError();
	char buffer[255] = { 0, };
	GetWindowTextA(handle, buffer, sizeof(buffer));
	return buffer;
}