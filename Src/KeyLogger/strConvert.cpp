#include "stdafx.h"
#include "strConvert.h"

using namespace std;

char* str::strConvert::ConvertWCtoC(wchar_t* str) {
	char* pStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	pStr = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

wchar_t* str::strConvert::ConverCtoWC(char* str) {
	wchar_t* pStr;
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	pStr = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;
}