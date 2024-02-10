//
// Created by ZHOU on 2024/2/9.
//

#ifndef IMGUI_MIUSI_H
#define IMGUI_MIUSI_H

#include"VirtualAtuoUtil.h"
#include <cmath>

void miusi_auto(int PL) {
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
        keyPress(&ip, DIK_RIGHT, 100);
        keyPress(&ip, DIK_RIGHT, 100);
        keyPress(&ip, DIK_SPACE, 100);
        Sleep(500 + getRandom());

        //清第一个房间怪
        keepRun(&ip,2000);
        keyPress(&ip, DIK_W, 100);
        keyPress(&ip, DIK_S, 100);
        Sleep(2000 + getRandom());

        //清第二个房间怪
        keepRun(&ip,1500);
        keyPress(&ip, DIK_E, 100);
        Sleep(1500 + getRandom());

        //清第BOSS
        keepRun(&ip,1500);
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_LCONTROL, 100);
        Sleep(6000 + getRandom());
//        keyPress(&ip, DIK_Y,100);
//        Sleep(5000+getRandom());
        keyPress(&ip, DIK_S, 200);
        Sleep(1000 + getRandom());
        keyPress(&ip, DIK_SPACE, 200);
        Sleep(3000 + getRandom());
        keyPress(&ip, DIK_GRAVE, 100);
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_X,3000);
        Sleep(2000 + getRandom());
        keyPress(&ip, DIK_ESCAPE, 100);
        Sleep(500+getRandom());
        if (i < count) {
            keyPress(&ip, DIK_F10, 100);
            Sleep(3000 + getRandom());
        } else {
            keyPress(&ip, DIK_F12, 100);
            Sleep(3000 + getRandom());
        }
    }
}

#endif //IMGUI_MIUSI_H
