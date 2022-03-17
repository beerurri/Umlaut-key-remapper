#include <Windows.h>
#include <iostream>

#define AE 0xC4
#define ae 0xE4
#define OE 0xD6
#define oe 0xF6
#define UE 0xDC
#define ue 0xFC
#define SS 0xDF

#define A 0x41
#define O 0x4F
#define U 0x55
#define S 0x53

bool flagA = false;
bool flagO = false;
bool flagU = false;
bool flagS = false;

bool mainCondition = false;
bool upperCase = false;

using namespace std;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

HHOOK hook;

KBDLLHOOKSTRUCT kbStruct;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam){
    if (nCode >= 0){
        if (wParam == WM_KEYDOWN){
            kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
            // if (kbStruct.vkCode == A)
            //     return -1;

            mainCondition = GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LMENU); // LeftCtrl + LeftAlt
            upperCase = GetKeyState(VK_CAPITAL) ^ (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT));

            if (mainCondition && kbStruct.vkCode == A && !flagA) {
                flagA = true;

                if (upperCase){
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = AE;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = AE;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }else{
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = ae;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = ae;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }
            }else
                flagA = false;
            
            if (mainCondition && kbStruct.vkCode == O && !flagO) {
                flagO = true;

                if (upperCase){
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = OE;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = OE;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }else{
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = oe;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = oe;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }
            }else
                flagO = false;
            
            if (mainCondition && kbStruct.vkCode == U && !flagU) {
                flagU = true;

                if (upperCase){
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = UE;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = UE;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }else{
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = ue;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = ue;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }
            }else
                flagU = false;
            
            if (mainCondition && kbStruct.vkCode == S && !flagS) {
                flagS = true;

                if (upperCase){
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = SS;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = SS;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }else{
                    INPUT in[2] = { 0, 0 };
                    in[0].type = INPUT_KEYBOARD;
                    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    in[0].ki.wScan = SS;

                    in[1].type = INPUT_KEYBOARD;
                    in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    in[1].ki.wScan = SS;

                    UINT uS = SendInput(2, in, sizeof(INPUT));
                    return -1;
                }
            }else
                flagS = false;
        }
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main(){
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);

    if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))){
        MessageBox(NULL, "The Remapper doesn't work", "Error", MB_ICONERROR);
        exit(0);
    }

    MSG message;

    while (true){
        GetMessage(&message, NULL, 0, 0);
    }
}