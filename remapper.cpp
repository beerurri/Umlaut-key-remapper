#include <Windows.h>

// VK key codes
#define A 0x41
#define O 0x4F
#define U 0x55
#define S 0x53

// Alt codes
#define AE 0xC4 // Ä
#define ae 0xE4 // ä
#define OE 0xD6 // Ö
#define oe 0xF6 // ö
#define UE 0xDC // Ü
#define ue 0xFC // ü
#define SS 0xDF // ß

// FOR DEBUGGING: 1 or 0
#define DEBUG 0

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

HHOOK hook;

KBDLLHOOKSTRUCT kbStruct;

bool mainCondition = false;
bool upperCase = false;

short ctrlState = false;
short altState = false;

bool flag = true;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        kbStruct = *((KBDLLHOOKSTRUCT *)lParam);

        ctrlState = GetAsyncKeyState(VK_LCONTROL); // LeftCtrl
        altState = GetAsyncKeyState(VK_LMENU);     // LeftAlt

        mainCondition = ctrlState && altState; // hotkeys combination

        upperCase = GetKeyState(VK_CAPITAL) ^ (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)); // CapsLk and Left/RightShift

        if (mainCondition && kbStruct.vkCode == A && kbStruct.flags == 0) //  kbStruct.flags 7th bit (the most significant bit) -> The value is 0 if the key is pressed and 1 if it is being released.
        {
            if (upperCase)
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = AE;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = AE;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
            else
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = ae;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = ae;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
        }

        if (mainCondition && kbStruct.vkCode == O && kbStruct.flags == 0)
        {
            if (upperCase)
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = OE;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = OE;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
            else
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = oe;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = oe;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
        }

        if (mainCondition && kbStruct.vkCode == U && kbStruct.flags == 0)
        {
            if (upperCase)
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = UE;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = UE;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
            else
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = ue;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = ue;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
        }

        if (mainCondition && kbStruct.vkCode == S && kbStruct.flags == 0)
        {
            if (upperCase)
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = SS;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = SS;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
            else
            {
                INPUT in[2] = {0, 0};
                in[0].type = INPUT_KEYBOARD;
                in[0].ki.dwFlags = KEYEVENTF_UNICODE;
                in[0].ki.wScan = SS;

                in[1].type = INPUT_KEYBOARD;
                in[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                in[1].ki.wScan = SS;

                UINT uS = SendInput(2, in, sizeof(INPUT));
                return -1;
            }
        }
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main()
{
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), DEBUG);

    if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
    {
        MessageBox(NULL, "The Umlaut Remapper doesn't work", "Error", MB_ICONERROR);
        exit(0);
    }

    MSG message;

    while (true)
    {
        GetMessage(&message, NULL, 0, 0);
    }
}