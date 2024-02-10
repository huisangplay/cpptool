//
// Created by ZHOU on 2024/2/9.
//

#ifndef IMGUI_VIRTUALATUOUTIL_H
#define IMGUI_VIRTUALATUOUTIL_H
#include <windows.h>
#include<dinput.h>
#include <random>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SPEED 1
#define INTERVAL 10
#define KEY_INTERVAL 100
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

int getRandom(int def=50) {
    std::random_device rd;  // 用于生成随机种子
    std::mt19937 eng(rd()); // 使用 Mersenne Twister 算法的随机数引擎
    std::uniform_int_distribution<int> distr(1, def); // 生成1到6之间的均匀分布的整数

    return distr(eng); // 生成随机数
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

void keyPress(INPUT *buffer, unsigned char key, int interval) {
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE;
    buffer->ki.wScan = key; // virtual-key code for the key


    SendInput(1, buffer, sizeof(INPUT));
    Sleep(interval);
    buffer->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, buffer, sizeof(INPUT));
    Sleep(10);
}

void keepRun(INPUT *ip,int time){
    keyPress(ip, DIK_RIGHT, 10);
    keyPress(ip, DIK_RIGHT, time);
}


#endif //IMGUI_VIRTUALATUOUTIL_H
