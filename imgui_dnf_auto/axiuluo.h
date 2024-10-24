//
// Created by ZHOU on 2024/2/9.
//

#ifndef IMGUI_AXIULUO_H
#define IMGUI_AXIULUO_H

#include"VirtualAtuoUtil.h"
#include <cmath>

void axiuluo_auto(int PL) {
    INPUT buffer;
    MouseSetup(&buffer);
    INPUT ip;
    KeyBoardSetup(&ip);
    int count = static_cast<int>(std::ceil(static_cast<double>(PL) / 12));
    //脚本主要逻辑
    Sleep(3000);

    for (int i = 1; i <= count; ++i) {
        std::cout<<"第"<<i<<"次进图..."<<std::endl;
        //buff
        keyPress(&ip, DIK_RIGHT, 100);
        keyPress(&ip, DIK_RIGHT, 100);
        keyPress(&ip, DIK_SPACE, 100);
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_Y, 100);
        Sleep(1300 + getRandom());

        //清第一个房间怪
        keyPress(&ip, DIK_RIGHT, 50);
        keyPress(&ip, DIK_RIGHT, 1400);
        keyPress(&ip, DIK_H, 100);
        Sleep(2000 + getRandom());

        //清第二个房间怪
        keyPress(&ip, DIK_RIGHT, 50);
        keyPress(&ip, DIK_RIGHT, 1300);
        keyPress(&ip, DIK_LALT, 500);
        Sleep(1000 + getRandom());

        //清第BOSS
        keyPress(&ip, DIK_RIGHT, 50);
        keyPress(&ip, DIK_RIGHT, 1300);
        keyPress(&ip, DIK_T, 100);
        Sleep(5000 + getRandom());

//        keyPress(&ip, DIK_Y,100);
//        Sleep(5000+getRandom());
        keyPress(&ip, DIK_GRAVE, 100);
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_ESCAPE, 100);
//        Sleep(500+getRandom());
        keyPress(&ip, DIK_X, 3000);
        Sleep(1000 + getRandom());

        if (i < count) {
            keyPress(&ip, DIK_F10, 100);
            Sleep(3000 + getRandom());
        } else {
            keyPress(&ip, DIK_F12, 100);
            Sleep(3000 + getRandom());
        }
    }
}

#endif //IMGUI_AXIULUO_H
