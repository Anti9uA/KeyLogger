#include "stdafx.h"
using namespace std;

string gettitle() {
	HWND handle = GetForegroundWindow();
	char buffer[255];
	GetWindowText(handle, LPWSTR(buffer), sizeof(buffer));
	return buffer;
}