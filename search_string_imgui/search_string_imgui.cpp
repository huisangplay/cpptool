#pragma comment(lib, "libdoctotext.a")
#pragma comment(lib, "podofo.lib")

#include<iostream>
#include<thread>
#include "imgui/imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "utils/windowsutil.h"
#include"utils/stringutil.h"
#include "utils/json.hpp"
#include"search.h"

using namespace std;
using json = nlohmann::json;

void search_string_by_thread();

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

static char search_string[1024];
static string search_path;
static set<string> filetypes;
static vector<string> output_filepaths;
static set<string> textfiletypes;
string action = "";
string showmessage = "";

int main(int, char **) {

    freopen("nul", "w", stderr);
    cout << UTF8_2_GBK(u8"开始读取 conf/filetypes.json 配置文件...") << endl;
    cout << UTF8_2_GBK(u8"支持文本类型数据类型:") << endl;
    ifstream jsonfile("conf/search_string_conf.json");
    json configJson = json::parse(jsonfile);

    int fileTypesCount = configJson["textfiletypes"].size();
    for (int i = 0; i < fileTypesCount; ++i) {
        cout << configJson["textfiletypes"][i] << endl;
        textfiletypes.insert(configJson["textfiletypes"][i]);
    }
    search_path = configJson["defaultSearchPath"];
    cout << UTF8_2_GBK(u8"读取默认搜索路径:" + search_path) << endl;
    search_path = UTF8_2_GBK(search_path);
    // Setup window
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


    //io.Fonts->AddFontFromFileTTF("fonts/SourceHanSansCN-Regular.otf", 22.0f, nullptr,
    //io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->AddFontFromFileTTF("fonts/SourceHanSansCN-Regular.otf", 22.0f, nullptr,
                                 io.Fonts->GetGlyphRangesChineseFull());
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //--------------主要页面逻辑
        //  Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGui::Begin(u8"字符串搜索工具");
            ImGui::PushItemWidth(500);

            ImGui::TextWrapped(
                    u8"本程序为在指定文件夹搜索指定字符串\n如需添加其他文本数据类型,请在conf/filetypes.json中配置\n查询多个字符串时,请用';'分隔,搜索结果保存在search_result.txt文件中\n");
            ImGui::TextWrapped(
                    u8"请选择要搜索的数据类型:");

            static bool wordtype = true;
            static bool ppttype = true;
            static bool exceltype = true;
            static bool texttype = true;
            static bool pdftype = true;
            ImGui::Checkbox(u8".doc .docx", &wordtype);
            ImGui::Checkbox(u8".ppt .pptx", &ppttype);
            ImGui::Checkbox(u8".xls .xlsx .csv", &exceltype);
            ImGui::Checkbox(u8".pdf", &pdftype);
            ImGui::Checkbox(u8"文本类型", &texttype);

            ImGui::InputText(u8"请输入要查询的字符串", search_string, IM_ARRAYSIZE(search_string));

            if (ImGui::Button(u8"选择搜索文件夹")) {
                search_path = OnSigBtnSelectInstallDir();
            }
            ImGui::SameLine();
            ImGui::Text(GBK_2_UTF8(search_path).c_str());

            if (ImGui::Button(u8"开始搜索")) {

                filetypes.clear();

                if (wordtype) {
                    filetypes.insert(".doc");
                    filetypes.insert(".docx");
                }

                if (ppttype) {
                    filetypes.insert(".ppt");
                    filetypes.insert(".pptx");
                }

                if (exceltype) {
                    filetypes.insert(".xls");
                    filetypes.insert(".xlsx");
                }

                if (pdftype) {
                    filetypes.insert(".pdf");
                }

                if (texttype) {
                    filetypes.insert(textfiletypes.begin(), textfiletypes.end());
                }

                showmessage = u8"搜索文件类型为: ";
                for (auto filetype: filetypes) showmessage = showmessage + filetype + " ";
                showmessage += "\n";

                output_filepaths.clear();
                action = u8"搜索中...";
                //创建一个线程去完成计算动作
                thread mythread(search_string_by_thread);
                //主线程子线程分离
                mythread.detach();
            }

            ImGui::TextWrapped(showmessage.c_str());

            if (output_filepaths.size() > 0) {

                for (auto output_filepath: output_filepaths) {
                    if (ImGui::Button(GBK_2_UTF8(output_filepath).c_str())) {
                        string cmd_string = "explorer /select," + output_filepath;
                        system(cmd_string.c_str());
                    }
                }

            }
            ImGui::Text(action.c_str());

            ImGui::End();
        }
        //--------------主要页面逻辑

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

void search_string_by_thread() {
    if (remove_surplus_spaces(search_string) == "") {
        showmessage = u8"请输入要搜索的字符串!";
        action = "";
        return;
    }
    if (search_path == "null") {
        showmessage = u8"请选择要搜索的文件夹!";
        action = "";
        return;
    }
    search_strs_main(search_path, UTF8_2_GBK(search_string), filetypes, output_filepaths);
    ofstream ofs;
    string filename = "search_result.txt";
    ofs.open(filename, ios::out);
    for (auto output_tempfilepath: output_filepaths) {
        ofs << output_tempfilepath << endl;
    }
    ofs.close();

    action = u8"搜索结束";
}
