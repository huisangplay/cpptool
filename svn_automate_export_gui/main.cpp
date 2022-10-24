#include<iostream>
#include<thread>
#include "imgui/imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include"search.h"
#include"idealsvnexport.h"
#include"cpcsvnexport.h"
#include "utils/stringutil.h"
#include "utils/windowsutil.h"
#include "utils/FTPClient.h"
#include "utils/json.hpp"

using namespace std;
using json = nlohmann::json;

void ideal_export();

void cpc_export();

string vec_to_string(vector<string> vec);

void svn_split(string svnline);

void ideal_upload_30_31_32();

void cpc_upload_10_11_12();

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include "backends/glfw3.h" // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static char svn_string[1024];
static string export_path = "F:\\submit";
static string showmessage;
static bool endflag = false;
static vector<string> exportfiles;
static string showfiles;
static char showchararray[65535];
static vector<int> svn_nums;
static string submit_path;
static string uploadmessage;
static string ideal_git_path;
static string cpc_git_path;

int main(int, char **) {
    //SetConsoleOutputCP(CP_UTF8);
    // Setup window
    cout << UTF8_2_GBK(u8"��ʼ��ȡ conf/svn_export.json �����ļ�...") << endl;

    ifstream jsonfile("conf/svn_export.json");
    json configJson = json::parse(jsonfile);

    ideal_git_path = configJson["ideal_git_path"];
    cout << UTF8_2_GBK(u8"ideal git�ļ���·��Ϊ:" + ideal_git_path) << endl;

    cpc_git_path = configJson["cpc_git_path"];
    cout << UTF8_2_GBK(u8"cpc git�ļ���·��Ϊ:" + cpc_git_path) << endl;

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    // Create window with graphics context
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1280, 720, u8"zhouhui tool", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.ConfigViewportsNoAutoMerge = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    io.Fonts->AddFontFromFileTTF("fonts/SourceHanSansCN-Regular.otf", 22.0f, nullptr,
                                 io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    // io.Fonts->AddFontFromFileTTF("Asset/Font/SourceHanSansCN-Normal.otf", 14.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //--------------��Ҫҳ���߼�
        //  Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGui::Begin(u8"svn�Զ���������");
            ImGui::PushItemWidth(500);

            ImGui::InputTextMultiline(
                    u8"������Ҫ���ص�svn�汾�ţ��Կո�������Զ�����...\n�����ļ���������ʽ-��ǰ������_������һ��svn��\n�״�ʹ����Ҫ���ñ�����Ŀgit�ļ���,����conf\\svn_export.json�ļ��н�������",
                    svn_string, IM_ARRAYSIZE(svn_string));

            if (ImGui::Button(u8"ѡ�񵼳�λ��")) {
                export_path = OnSigBtnSelectInstallDir();
            }
            ImGui::SameLine();
            ImGui::Text(GBK_2_UTF8(export_path).c_str());

            if (ImGui::Button(u8"ideal����")) {
                uploadmessage = "";
                endflag = false;
                exportfiles.clear();
                showmessage = u8"ideal svn�ļ�������...\n";
                //����һ���߳�ȥ��ɼ��㶯��
                thread mythread(ideal_export);
                //���߳����̷߳���
                mythread.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(u8"cpc����")) {
                uploadmessage = "";
                endflag = false;
                exportfiles.clear();
                showmessage = u8"cpc svn�ļ�������...\n";
                //����һ���߳�ȥ��ɼ��㶯��
                thread mythread(cpc_export);
                //���߳����̷߳���
                mythread.detach();
            }

            ImGui::Text(showmessage.c_str());

            if (endflag) {

                if (submit_path.find("ideal") != string::npos) {
                    if (ImGui::Button(u8"ideal��ʱ�ļ����")) {
                        string copystring;
                        for(int svn_num:svn_nums) copystring+=to_string(svn_num)+" ";
                        copystring+="\n";
                        copystring+= vec_to_string(exportfiles);
                        CopyToClipboard(copystring.c_str());
                        showmessage+=u8"��ʱ�ļ����������Ϣ�Ѹ�����ճ����.";
                        system("start chrome.exe http://10.11.49.173:8080/index");
                    }
                    ImGui::SameLine();
                    ImGui::Text(u8"�����ʱ�ļ������Զ�����svn�ż��ļ��б�");

                    ImGui::Text(u8"\n����ideal�ļ��б�");
                    strcpy(showchararray, showfiles.c_str());
                    ImGui::InputTextMultiline(u8" ", showchararray, IM_ARRAYSIZE(showchararray));
                    ImGui::SameLine();
                    if (ImGui::Button(u8"���ļ�λ��")) {
                        string cmd_string = "explorer /e," + submit_path;
                        system(cmd_string.c_str());
                    }

                    ImGui::SameLine();
                    if (ImGui::Button(u8"�ϴ�ideal 30 31 32 ������")) {
                        ideal_upload_30_31_32();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(u8"ͬ��ideal git")) {
                        string cmdstr = "TortoiseGitProc /path:\"" + ideal_git_path + "\"     /command:pull";
                        system(cmdstr.c_str());
                        cmdstr = " xcopy /QEY " + submit_path + UTF8_2_GBK(u8"\\��Ŀ���� " + ideal_git_path);
                        system(cmdstr.c_str());
                        cmdstr = "TortoiseGitProc /path:\"" + ideal_git_path + "\"     /command:commit -a";
                        system(cmdstr.c_str());

                    }
                }
                if (submit_path.find("cpc") != string::npos) {
                    if (ImGui::Button(u8"cpc��ʱ�ļ����")) {
                        string copystring;
                        for(int svn_num:svn_nums) copystring+=to_string(svn_num)+" ";
                        copystring+="\n";
                        copystring+= vec_to_string(exportfiles);
                        CopyToClipboard(copystring.c_str());
                        showmessage+=u8"��ʱ�ļ����������Ϣ�Ѹ�����ճ����.";
                        system("start chrome.exe http://10.11.49.173:8088/index");
                    }
                    ImGui::SameLine();
                    ImGui::Text(u8"�����ʱ�ļ������Զ�����svn�ż��ļ��б�");

                    ImGui::Text(u8"\n����cpc�ļ��б�");
                    strcpy(showchararray, showfiles.c_str());
                    ImGui::InputTextMultiline(u8" ", showchararray, IM_ARRAYSIZE(showchararray));
                    ImGui::SameLine();
                    if (ImGui::Button(u8"���ļ�λ��")) {
                        string cmd_string = "explorer /e," + submit_path;
                        system(cmd_string.c_str());
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(u8"�ϴ�cpc 10 11 12 ������")) {
                        cpc_upload_10_11_12();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(u8"ͬ��cpc git")) {
                        string cmdstr = "TortoiseGitProc /path:\"" + cpc_git_path + "\"     /command:pull";
                        system(cmdstr.c_str());
                        cmdstr = " xcopy /QEY " + submit_path + UTF8_2_GBK(u8"\\trunk\\code " + cpc_git_path);
                        system(cmdstr.c_str());
                        cmdstr = "TortoiseGitProc /path:\"" + cpc_git_path + "\"     /command:commit -a";
                        system(cmdstr.c_str());

                    }
                }
                ImGui::Text(uploadmessage.c_str());
            }


            ImGui::End();
        }
        //--------------��Ҫҳ���߼�

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void ideal_export() {

    if (remove_surplus_spaces(svn_string).size() == 0) {
        showmessage = u8"��������Ҫ������svn��...";
        return;
    }
    if (export_path == "null") {
        showmessage = u8"��ѡ�񵼳����ļ���...";
        return;
    }
    svn_nums.clear();
    svn_split(svn_string);

    submit_path = export_path + "\\ideal_" + getCurrentYearMonthDayString() + "_svn" + to_string(svn_nums[0]);

    showmessage = showmessage + u8"�����ļ�λ��:" + submit_path + "\n";
    ideal_svn_export(svn_nums, submit_path, exportfiles);
    endflag = true;
    showfiles = GBK_2_UTF8(vec_to_string(exportfiles));
}

void cpc_export() {
    if (remove_surplus_spaces(svn_string).size() == 0) {
        showmessage = u8"��������Ҫ������svn��...";
        return;
    }
    if (export_path == "null") {
        showmessage = u8"��ѡ�񵼳����ļ���...";
        return;
    }
    svn_nums.clear();
    svn_split(svn_string);

    submit_path = export_path + "\\cpc_" + getCurrentYearMonthDayString() + "_svn" + to_string(svn_nums[0]);

    showmessage = showmessage + u8"�����ļ�λ��:" + submit_path + "\n";
    cpc_svn_export(svn_nums, submit_path, exportfiles);
    endflag = true;
    showfiles = GBK_2_UTF8(vec_to_string(exportfiles));
}

string vec_to_string(vector<string> vec) {
    string result;
    for (string str: vec) {
        result = result + str + "\n";
    }
    return result;
}

void svn_split(string svnline) {
    svnline = remove_surplus_spaces(svnline);
    vector<string> svn_strs = split(svnline, ' ');
    for (int i = 0; i < svn_strs.size(); ++i) {
        svn_nums.push_back(atoi(svn_strs.at(i).c_str()));
    }
    sort(svn_nums.begin(), svn_nums.end());
    showmessage = showmessage + u8"svn�汾��������" + to_string(svn_nums.size()) + "\n";
    showmessage = showmessage + u8"�����İ汾:";
    for (int svn_num: svn_nums) {
        showmessage = showmessage + to_string(svn_num) + " ";
    }
    showmessage += "\n";
}

void ideal_upload_30_31_32() {
    uploadmessage = "";
    vector<string> ips;
    ips.push_back("10.11.13.30");
    ips.push_back("10.11.13.31");
    ips.push_back("10.11.13.32");

    for (auto ip: ips) {
        uploadmessage += u8"\n�ϴ�" + ip + u8"��������...";
        embeddedmz::CFTPClient FTPClient([](const std::string &strLogMsg) { std::cout << strLogMsg << endl; });
        FTPClient.InitSession(ip, 21, "windch", "ide2012w");
        for (auto exportfile: exportfiles) {
            string localpath = submit_path + exportfile;
            replace(localpath.begin(), localpath.end(), '/', '\\');
            string serverpath = "/ptc/Windchill/ideal" + exportfile.substr(9);
            //FTPClient.UploadFile(submit_path+exportfile, "/ptc/Windchill/ideal"+exportfile.substr(8));
            if (!FTPClient.UploadFile(GBK_2_UTF8(localpath), GBK_2_UTF8(serverpath),true)) {
                uploadmessage += u8"\n�ϴ�" + ip + u8"������ʧ��...�������ϴ�";
                return;
            }
        }
    }
    uploadmessage += u8"�ϴ����";
}

void cpc_upload_10_11_12() {
    uploadmessage = "";
    vector<string> ips;
    ips.push_back("10.11.13.10");
    ips.push_back("10.11.13.11");
    ips.push_back("10.11.13.12");

    for (auto ip: ips) {
        uploadmessage += u8"\n�ϴ�" + ip + u8"��������...";
        embeddedmz::CFTPClient FTPClient([](const std::string &strLogMsg) { std::cout << strLogMsg << endl; });
        FTPClient.InitSession(ip, 21, "windch", "cpc0318w");
        for (auto exportfile: exportfiles) {
            string localpath = submit_path + exportfile;
            replace(localpath.begin(), localpath.end(), '/', '\\');
            string serverpath = "/ptc/Windchill/CPC" + exportfile.substr(11);
            //FTPClient.UploadFile(submit_path+exportfile, "/ptc/Windchill/ideal"+exportfile.substr(8));
            cout<<"server path:"<<serverpath<<endl;
            if (!FTPClient.UploadFile(GBK_2_UTF8(localpath), GBK_2_UTF8(serverpath),true)) {
                uploadmessage += u8"\n�ϴ�" + ip + u8"������ʧ��...�������ϴ�";
                return;
            }
        }
    }
    uploadmessage += u8"�ϴ����";
}