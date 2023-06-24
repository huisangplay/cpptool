#include <windows.h>
#include "include/cef_command_line.h"
#include "simple_app.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine,
                     int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int exit_code;

    void *sandbox_info = nullptr;

    // Provide CEF with command-line arguments.
    CefMainArgs main_args(hInstance);

    // CEF applications have multiple sub-processes (render, GPU, etc) that share
    // the same executable. This function checks the command-line and, if this is
    // a sub-process, executes the appropriate logic.
    exit_code = CefExecuteProcess(main_args, nullptr, sandbox_info);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    // Parse command-line arguments for use in this method.
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());

    // Specify CEF global settings here.
    CefSettings settings;

    if (command_line->HasSwitch("enable-chrome-runtime")) {
        // Enable experimental Chrome runtime. See issue #2969 for details.
        settings.chrome_runtime = true;
    }


    // SimpleApp implements application-level callbacks for the browser process.
    // It will create the first browser instance in OnContextInitialized() after
    // CEF has initialized.
    CefRefPtr<SimpleApp> app(new SimpleApp);

    // Initialize CEF.
    CefInitialize(main_args, settings, app.get(), sandbox_info);


    // Run the CEF message loop. This will block until CefQuitMessageLoop() is
    // called.
    CefRunMessageLoop();

    // Shut down CEF.
    CefShutdown();

    return 0;
}
