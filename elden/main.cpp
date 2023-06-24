#include <windows.h>
#include<dinput.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SPEED 1
#define INTERVAL 10
#define KEY_INTERVAL 100
#include<iostream>
void moveMouseByTimeAndCoordinate(int x, int y, int time, INPUT *buffer);
void keyPress(INPUT *buffer, unsigned char key,int interval);
void keyPress(INPUT *buffer, unsigned char key);

void MouseSetup(INPUT *buffer) {
    buffer->type = INPUT_MOUSE;
    buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.mouseData = 0;
    buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
    buffer->mi.time = 0;
    buffer->mi.dwExtraInfo = 0;
}

void KeyBoardSetup(INPUT *buffer) {
    buffer->type = INPUT_KEYBOARD;
    buffer->ki.time = 0;
    buffer->ki.wVk = 0;
    buffer->ki.dwExtraInfo = 0;
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE;
}

void MouseMoveAbsolute(INPUT *buffer, int x, int y) {
    buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH)) * SPEED;
    buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT)) * SPEED;
    buffer->mi.dwFlags = (MOUSEEVENTF_MOVE);

    SendInput(1, buffer, sizeof(INPUT));
}


void MouseClickLeft(INPUT *buffer) {
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
    SendInput(1, buffer, sizeof(INPUT));

    Sleep(KEY_INTERVAL);

    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
    SendInput(1, buffer, sizeof(INPUT));
}
void MouseClickMid(INPUT *buffer) {
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN);
    SendInput(1, buffer, sizeof(INPUT));

    Sleep(KEY_INTERVAL);

    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEUP);
    SendInput(1, buffer, sizeof(INPUT));
}

void MouseClickRight(INPUT *buffer) {
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN);
    SendInput(1, buffer, sizeof(INPUT));

    Sleep(KEY_INTERVAL);

    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP);
    SendInput(1, buffer, sizeof(INPUT));
}


int main(int argc, char *argv[]) {
    INPUT buffer;
    MouseSetup(&buffer);
    INPUT ip;
    KeyBoardSetup(&ip);

    //脚本主要逻辑
    Sleep(3000);

    while(true){

        keyPress(&ip, DIK_UP,50);
        keyPress(&ip, DIK_E);

        Sleep(1000);

        MouseClickMid(&buffer);
        Sleep(500);

        MouseClickRight(&buffer);
        Sleep(2500);
        MouseClickRight(&buffer);
        Sleep(2500);
        MouseClickRight(&buffer);
        Sleep(2500);
        MouseClickRight(&buffer);
		
        Sleep(2500);
        MouseClickRight(&buffer);
        Sleep(3500);

        keyPress(&ip, VK_RETURN);
        Sleep(5 000);
		
		
		
		keyPress(&ip, VK_RETURN,99);
		Sleep(5000);
		//W
		keyPress(&ip, 0x57,33000);
		Sleep(9000);
		
		//X
		keyPress(&ip, 0x58,99);
		Sleep(1000);
		
		keyPress(&ip, VK_RETURN,99);
		Sleep(900);
    }

}

void moveMouseByTimeAndCoordinate(int x, int y, int time, INPUT *buffer) {
    for (int i = 0; i <= time; i += INTERVAL) {
        MouseMoveAbsolute(buffer, x, y);
        Sleep(INTERVAL);
    }
}

void keyPress(INPUT *buffer, unsigned char key) {
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE;
    buffer->ki.wScan = key; // virtual-key code for the key


    SendInput(1, buffer, sizeof(INPUT));
    Sleep(KEY_INTERVAL);
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, buffer, sizeof(INPUT));
}

void keyPress(INPUT *buffer, unsigned char key,int interval) {
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE;
    buffer->ki.wScan = key; // virtual-key code for the key


    SendInput(1, buffer, sizeof(INPUT));
    Sleep(interval);
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, buffer, sizeof(INPUT));
}