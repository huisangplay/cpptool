//
// Created by ZHOU on 2024/2/10.
//

#ifndef IMGUI_ALLROLE_H
#define IMGUI_ALLROLE_H

#include<map>
#include"VirtualAtuoUtil.h"
#include <cmath>
#include<iostream>
#include <unordered_map>
#include <functional>
#include"naima.h"
#include"miusi.h"
#include"jianhun.h"
#include "kuangzhan.h"
#include"jianying.h"
#include"axiuluo.h"
#include"jiandi.h"
#include"renying.h"
#include"lvren.h"
#include <fstream>
#include "json.hpp"
#include "naiba.h"

extern int SWITCH_ROLE_CURSOR_X = 1046;
extern int SWITCH_ROLE_CURSOR_Y = 733;
using json = nlohmann::json;

void allRole_auto() {
    Sleep(3000);
    INPUT buffer;
    MouseSetup(&buffer);
    INPUT ip;
    KeyBoardSetup(&ip);

    std::ifstream auto_dnf_config_file("auto_dnf_config.json");
    json auto_dnf_config = json::parse(auto_dnf_config_file);

    // 获取 "Sequence" 对象
    nlohmann::json sequenceJson = auto_dnf_config["Sequence"];

    // 使用 std::map 来按顺序存储键值对
    std::map<int, nlohmann::json> orderedSequence;

    // 遍历 "Sequence" 对象的键值对，将其按顺序存入 std::map
    for (const auto& pair : sequenceJson.items()) {
        int key = std::stoi(pair.key());
        orderedSequence[key] = pair.value();
    }

    // 遍历 "Sequence" 对象的键值对
    for (const auto& pair : orderedSequence) {
        int roleMapKey = pair.first;
        const nlohmann::json& value = pair.second;

        std::string role = value["role"];
        int pl = value["PL"];

        std::cout << "roleMapKey: " << roleMapKey << ", Role: " << role << ", PL: " << pl << std::endl;

        if(role=="NULL"||pl==0){
            keyPress(&ip, DIK_RIGHT, 50 + getRandom());
            Sleep(1000 + getRandom(100));
            continue;
        }

        keyPress(&ip, DIK_SPACE, 50 + getRandom());
        Sleep(2000 + getRandom(100));

        keyPress(&ip, DIK_RIGHT, 1500 + getRandom(500));
        keyPress(&ip, DIK_SPACE, 50 + getRandom());
        Sleep(1000 + getRandom(100));

        keyPress(&ip, DIK_RIGHT, 2000 + getRandom(500));
        keyPress(&ip, DIK_SPACE, 50 + getRandom());
        Sleep(500 + getRandom(100));

        if (role == "奶妈") {
            std::cout << "开始奶妈自动刷深渊" << std::endl;
            naima_auto(pl);
        } else if (role == "缪斯") {
            std::cout << "开始缪斯自动刷深渊" << std::endl;
            miusi_auto(pl);
        } else if (role == "剑魂") {
            std::cout << "开始剑魂自动刷深渊" << std::endl;
            jianhun_auto(pl);
        } else if (role == "狂战") {
            std::cout << "开始狂战自动刷深渊" << std::endl;
            kuangzhan_auto(pl);
        } else if (role == "剑影") {
            std::cout << "开始剑影自动刷深渊" << std::endl;
            jianying_auto(pl);
        } else if (role == "修罗") {
            std::cout << "开始修罗自动刷深渊" << std::endl;
            axiuluo_auto(pl);
        } else if (role == "剑帝") {
            std::cout << "开始剑帝自动刷深渊" << std::endl;
            jiandi_auto(pl);
        } else if (role == "旅人") {
            std::cout << "开始旅人自动刷深渊" << std::endl;
            lvren_auto(pl);
        } else if (role == "刃影") {
            std::cout << "开始刃影自动刷深渊" << std::endl;
            renying_auto(pl);
        }else if (role == "奶爸") {
            std::cout << "开始奶爸自动刷深渊" << std::endl;
            naiba_auto(pl);
        }
        keyPress(&ip, DIK_ESCAPE, 50 + getRandom());
        Sleep(1000 + getRandom(100));

        // 设置鼠标坐标为固定值
        SetCursorPos(SWITCH_ROLE_CURSOR_X, SWITCH_ROLE_CURSOR_Y);
        Sleep(1000 + getRandom(100));

        MouseClickLeft(&buffer);
        Sleep(1500 + getRandom(100));

        keyPress(&ip, DIK_RIGHT, 50+ getRandom());
        Sleep(500 + getRandom(100));

    }
}

#endif //IMGUI_ALLROLE_H
