#pragma once
#define ULEN 100
#include "stdafx.h"

using namespace std;

namespace file {
	class fileManager {
	private:
		FILE* ff;
		TCHAR username[ULEN];
		DWORD usersize;
	public:
		fileManager() {
			ff = NULL;
			username[ULEN] = { 0, };
			usersize = sizeof(username) / sizeof(username[0]);
		};
		char* getlogfilename();
		char* getlogfilepath(char* filename);
		void logger(string key);
		int getfilesize();
	};
}