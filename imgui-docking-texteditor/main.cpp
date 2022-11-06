#include<iostream>
#include<thread>
#include <fstream>
#include "imgui/imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "utils/windowsutil.h"
#include"utils/stringutil.h"
#include "utils/json.hpp"
#include "TextEditor.h"
using namespace std;
using json = nlohmann::json;
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include "backends//glfw3.h" // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static char search_string[256];
static string search_path;
// Data

int main(int, char **) {
    TextEditor editor;
    SetConsoleOutputCP(CP_UTF8);

    cout<<u8"开始读取配置文件..."<<endl;
    cout<<u8"支持文件类型为:"<<endl;
    ifstream fileTypesStream("filetypes.json");
    json fileTypeJson = json::parse(fileTypesStream);
    int fileTypesCount=fileTypeJson["filetypes"].size();
    for(int i=0;i<fileTypesCount;++i){
        cout<<fileTypeJson["filetypes"][i]<<endl;
    }

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
    GLFWwindow *window = glfwCreateWindow(1280, 720, "zhouhui tool", NULL, NULL);
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


    io.Fonts->AddFontFromFileTTF("../fonts/SourceHanSansCN-Regular.otf", 25.0f, nullptr,
                                 io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    // io.Fonts->AddFontFromFileTTF("Asset/Font/SourceHanSansCN-Normal.otf", 14.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Text Editor Demo", nullptr);
        ImGui::SetWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
        ImGui::InputTextMultiline(u8"请输入要查询的字符串", search_string, IM_ARRAYSIZE(search_string));

        editor.SetColorizerEnable(true);

        if (ImGui::Button("Dark"))
        {
            editor.SetPalette(TextEditor::GetDarkPalette());
        }
        if (ImGui::Button("Light"))
        {
            editor.SetPalette(TextEditor::GetLightPalette());
        }if (ImGui::Button("Retro blue"))
        {
            editor.SetPalette(TextEditor::GetRetroBluePalette());
        }
        if (ImGui::Button(u8"选择搜索文件夹")) {
            search_path = OnSigBtnSelectInstallDir();
            search_path = GBK_2_UTF8(search_path);
            cout << search_path << endl;
        }
        //显示在同一行
        ImGui::SameLine();
        ImGui::Text(search_path.c_str());
        editor.Render("TextEditor",ImVec2(500, 400),true);
        editor.SetShowWhitespaces(true);
        if (ImGui::Button(u8"选择搜索文件夹")) {
            search_path = OnSigBtnSelectInstallDir();
            search_path = GBK_2_UTF8(search_path);
            cout << search_path << endl;
        }

        if(ImGui::Button(u8"输出输入框字符串")){
            ImGui::Text(editor.GetText().c_str());
        }
        ImGui::Text(editor.GetText().c_str());

        ImGui::End();

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
