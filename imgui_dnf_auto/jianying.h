//
// Created by ZHOU on 2024/2/9.
//

#ifndef IMGUI_JIANYING_H
#define IMGUI_JIANYING_H

#include"VirtualAtuoUtil.h"
#include <cmath>

void jianying_auto(int PL) {
    INPUT buffer;
    MouseSetup(&buffer);
    INPUT ip;
    KeyBoardSetup(&ip);
    int count = static_cast<int>(std::ceil(static_cast<double>(PL) / 8));

    //脚本主要逻辑
    Sleep(3000);

    for (int i = 1; i <= count; ++i) {
        std::cout<<"第"<<i<<"次进图..."<<std::endl;

        //buff
        keyPress(&ip, DIK_UP, 100);
        keyPress(&ip, DIK_UP, 100);
        keyPress(&ip, DIK_SPACE, 100);

        Sleep(1300 + getRandom());
        keyPress(&ip, DIK_DOWN, 100);
        keyPress(&ip, DIK_DOWN, 100);

        //清第一个房间怪
        keepRun(&ip,1500);
        keyPress(&ip, DIK_Q, 100);
        Sleep(100 + getRandom());
        keyPress(&ip, DIK_W, 100);
        Sleep(500 + getRandom());

        //清第二个房间怪
        keepRun(&ip,800);
        keyPress(&ip, DIK_E, 500);
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_D, 100);
        Sleep(1000 + getRandom());

        //清第BOSS
        keepRun(&ip,500);
        keyPress(&ip, DIK_R, 100);
        Sleep(1000 + getRandom());
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_G, 100);
        Sleep(4000 + getRandom());
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

#endif //IMGUI_JIANYING_H
