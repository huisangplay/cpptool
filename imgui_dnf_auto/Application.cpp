
#include"Application.h"
#include <Windows.h>
#include<iostream>
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
#include "naiba.h"

static int naimaPL = 188;
static int miusiPL = 188;
static int jianhunPL = 188;
static int kuangzhanPL = 188;
static int jianyingPL = 188;
static int axiuluoPL = 188;
static int jiandiPL = 188;
static int lvrenPL = 188;
static int renyingPL = 188;
static int naibaPL = 188;
static int PLInputLen = 50;
static int changed = false;
static int roleIndex=0;
static ImGuiTheme::ImGuiTweakedTheme imGuiTweakedTheme;

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

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Options")) {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) !=
                                                         0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) !=
                                                          0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "",
                                    (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) !=
                                    0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) !=
                                                                0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "",
                                    (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0,
                                    opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();
                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }

        //-------------------------------
        ImGui::Begin(u8"主题设置");
        if (ImGuiTheme::ShowThemeTweakGui(&imGuiTweakedTheme)) {
            ApplyTweakedTheme(imGuiTweakedTheme);
        }
        ImGui::End();
        //---------------------------

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
            allRole_auto(roleIndex);
        }
        ImGui::SameLine();
        ImGui::InputInt("start", &roleIndex);


        //奶妈
        if (ImGui::Button(u8"奶妈")) {
            naima_auto(naimaPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(0);
        ImGui::InputInt("疲劳值", &naimaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();


        //缪斯
        if (ImGui::Button(u8"缪斯")) {
            miusi_auto(miusiPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(1);
        ImGui::InputInt("疲劳值", &miusiPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //奶爸
        if (ImGui::Button(u8"奶爸")) {
            naiba_auto(naibaPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(9);
        ImGui::InputInt("疲劳值", &naibaPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //剑魂
        if (ImGui::Button(u8"剑魂")) {
            jianhun_auto(jianhunPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(2);
        ImGui::InputInt("疲劳值", &jianhunPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //狂战
        if (ImGui::Button(u8"狂战")) {
            kuangzhan_auto(kuangzhanPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(3);
        ImGui::InputInt("疲劳值", &kuangzhanPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //剑影
        if (ImGui::Button(u8"剑影")) {
            jianying_auto(jianyingPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(4);
        ImGui::InputInt("疲劳值", &jianyingPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //修罗
        if (ImGui::Button(u8"修罗")) {
            axiuluo_auto(axiuluoPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(5);
        ImGui::InputInt("疲劳值", &axiuluoPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //剑帝
        if (ImGui::Button(u8"剑帝")) {
            jiandi_auto(jiandiPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(6);
        ImGui::InputInt("疲劳值", &jiandiPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //旅人
        if (ImGui::Button(u8"旅人")) {
            lvren_auto(lvrenPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(7);
        ImGui::InputInt("疲劳值", &lvrenPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        //刃影
        if (ImGui::Button(u8"刃影")) {
            renying_auto(renyingPL);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(PLInputLen);
        ImGui::PushID(8);
        ImGui::InputInt("疲劳值", &renyingPL, 0, 0, ImGuiInputTextFlags_CharsDecimal);
        ImGui::PopID();

        ImGui::End();
        ImGui::End();
    }
}
