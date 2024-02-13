//
// Created by ZHOU on 2024/2/9.
//

#ifndef IMGUI_JIANHUN_H
#define IMGUI_JIANHUN_H

#include"VirtualAtuoUtil.h"
#include <cmath>

void jianhun_auto(int PL) {
    INPUT buffer;
    MouseSetup(&buffer);
    INPUT ip;
    KeyBoardSetup(&ip);
    int count = static_cast<int>(std::ceil(static_cast<double>(PL) / 8));

    //脚本主要逻辑
    Sleep(3000);
    for (int i = 1; i <= count; ++i) {
        std::cout << "第" << i << "次进图..." << std::endl;

        //buff
        keyPress(&ip, DIK_RIGHT, 50);
        keyPress(&ip, DIK_RIGHT, 100);
        keyPress(&ip, DIK_SPACE, 100);
        Sleep(500 + getRandom());

        //清第一个房间怪
        keepRun(&ip,2200);
        keyPress(&ip, DIK_Q, 100);
        keyPress(&ip, DIK_Q, 100);
        Sleep(1000 + getRandom());

        //清第二个房间怪
        keepRun(&ip,1300);
        keyPress(&ip, DIK_R, 100);
        Sleep(500 + getRandom());

        //清第BOSS
        keepRun(&ip,2000);
        Sleep(300 + getRandom());
        keyPress(&ip, DIK_UP, 100);
        keyPress(&ip, DIK_SPACE, 100);
        Sleep(4000 + getRandom());
        keyPress(&ip, DIK_G, 50);
        Sleep(100 + getRandom());
        keyPress(&ip, DIK_S, 50);
        Sleep(100 + getRandom());
        keyPress(&ip, DIK_SPACE, 50);
        Sleep(1000 + getRandom());
        keyPress(&ip, DIK_GRAVE, 100);
        Sleep(500 + getRandom());
        keyPress(&ip, DIK_ESCAPE, 100);
        Sleep(500+getRandom());
        keyPress(&ip, DIK_X,3000);
        Sleep(2000 + getRandom());

        if (i < count) {
            keyPress(&ip, DIK_F10, 100);
            Sleep(3000 + getRandom());
        } else {
            keyPress(&ip, DIK_F12, 100);
            Sleep(3000 + getRandom());
        }
    }
}

#endif //IMGUI_JIANHUN_H
