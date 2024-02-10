//
// Created by ZHOU on 2023/6/23.
//
#include <Windows.h>
#include<iostream>
#include "Application.h"
#include"naima.h"
#include"miusi.h"
#include"jianhun.h"
#include "kuangzhan.h"
#include"jianying.h"
#include"axiuluo.h"
#include"jiandi.h"
#include"renying.h"
#include"lvren.h"
#include"AllRole.h"

static int naimaPL = 188;
static int buttonLen = 500;
static int PLInputLen = 50;


namespace MyApp {
    void RenderUI() {

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();
                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }


        ImGui::Begin("DNF自动刷深渊脚本");

        if (ImGui::Button(u8"获取选择角色按钮坐标")) {
            Sleep(5000);
            POINT cursorPoint;
            GetCursorPos(&cursorPoint);

            int mouseX = cursorPoint.x;
            int mouseY = cursorPoint.y;

            std::cout << "Current mouse coordinates: (" << mouseX << ", " << mouseY << ")" << std::endl;
        }

        if (ImGui::Button(u8"设置切换角色按钮坐标值")) {
            // 设置鼠标坐标为固定值
            SetCursorPos(SWITCH_ROLE_CURSOR_X, SWITCH_ROLE_CURSOR_Y);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("X", &SWITCH_ROLE_CURSOR_X, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("Y", &SWITCH_ROLE_CURSOR_Y, 0, 0, ImGuiInputTextFlags_CharsDecimal);


        if (ImGui::Button(u8"全角色自动刷深渊")) {
            allRole_auto();
        }

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"奶妈")) {
            naima_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"缪斯")) {
            miusi_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"剑魂")) {
            jianhun_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"狂战")) {
            kuangzhan_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"剑影")) {
            jianying_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"修罗")) {
            axiuluo_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"剑帝")) {
            jiandi_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"旅人")) {
            lvren_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);

        ImGui::PushItemWidth(buttonLen);
        if (ImGui::Button(u8"刃影")) {
            renying_auto(naimaPL);
        }
        ImGui::SameLine();
        // 设置输入框的宽度为200
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::End();
        ImGui::End();
    }
}
