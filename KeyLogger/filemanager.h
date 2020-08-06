#pragma once
#include "stdafx.h"
using namespace std;

char* getlogfilename();
char* getlogfilepath(const char* filename);
void logger(string key);
int getfilesize();
wchar_t* ConvertCtoWC(char* str);
char* ConvertWCtoC(wchar_t* str);