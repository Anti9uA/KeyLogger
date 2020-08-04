#include "stdafx.h"

time_t t = time(NULL);
struct tm tm = *localtime(&t);
char username[50];

char* getlogfilename() {
	char time[15] = { 0, };
	sprintf(time, "%d", tm.tm_year);
	char month[10] = { 0, };
	sprintf(month, "%d", tm.tm_mon);
	char day[10] = { 0, };
	sprintf(month, "%d", tm.tm_mday);
	strcat(time, month); strcat(time, day); strcat(time, ".log");
	return time;
}

string getlogfilepath(char* filename) {
	GetUserName(LPWSTR(username), LPDWORD(sizeof(username)));
	char dirpath[50] = "C:\\Users";
	char filepath[50] = "C:\\Users";
	PathAppend(LPWSTR(dirpath), LPWSTR(username));
	PathAppend(LPWSTR(dirpath), L"Appdata\\Roaming\\Windows");
	if (!PathFileExists(LPWSTR(dirpath))) {
		_mkdir(dirpath);
	}
	PathAppend(LPWSTR(filepath), LPWSTR(username));
	PathAppend(LPWSTR(filepath), L"Appdata\\Roaming\\Windows");
	PathAppend(LPWSTR(filepath), LPCWSTR(filename));
	return filepath;
}

void logger(string key) {
	key = key.replace(key.find("'"), 1, "");
	fstream f;
	char ch_key[100] = { 0, };
	strcpy(ch_key, key.c_str());
	f.open(getlogfilepath(getlogfilename()));
	f.write(ch_key, sizeof(ch_key));
	f.close();
}

int getfilesize() {
	int rst = 0;
	char path[100] = { 0, };
	strcpy(path, getlogfilepath(getlogfilename()).c_str());
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