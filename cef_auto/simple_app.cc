// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"

#include <string>
#include <iostream>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "simple_handler.h"

namespace {

// When using the Views framework this object provides the delegate
// implementation for the CefWindow that hosts the Views-based browser.
    class SimpleWindowDelegate : public CefWindowDelegate {
    public:
        explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_view)
                : browser_view_(browser_view) {}

        void OnWindowCreated(CefRefPtr<CefWindow> window) override {
            // Add the browser view and show the window.
            window->AddChildView(browser_view_);
            window->Show();

            // Give keyboard focus to the browser view.
            browser_view_->RequestFocus();
        }

        void OnWindowDestroyed(CefRefPtr<CefWindow> window) override {
            browser_view_ = nullptr;
        }

        bool CanClose(CefRefPtr<CefWindow> window) override {
            // Allow the window to close if the browser says it's OK.
            CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
            if (browser) {
                return browser->GetHost()->TryCloseBrowser();
            }
            return true;
        }

        CefSize GetPreferredSize(CefRefPtr<CefView> view) override {
            return CefSize(800, 600);
        }

    private:
        CefRefPtr<CefBrowserView> browser_view_;

    IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
        DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);
    };

    class SimpleBrowserViewDelegate : public CefBrowserViewDelegate {
    public:
        SimpleBrowserViewDelegate() {}

        bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view,
                                       CefRefPtr<CefBrowserView> popup_browser_view,
                                       bool is_devtools) override {
            // Create a new top-level Window for the popup. It will show itself after
            // creation.
            CefWindow::CreateTopLevelWindow(
                    new SimpleWindowDelegate(popup_browser_view));

            // We created the Window.
            return true;
        }

    private:
    IMPLEMENT_REFCOUNTING(SimpleBrowserViewDelegate);
        DISALLOW_COPY_AND_ASSIGN(SimpleBrowserViewDelegate);
    };

}  // namespace

SimpleApp::SimpleApp() {}

void SimpleApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line =
            CefCommandLine::GetGlobalCommandLine();

    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<SimpleHandler> handler(new SimpleHandler(true));

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    // Create the BrowserView.
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
            handler, "", browser_settings, nullptr, nullptr,
            new SimpleBrowserViewDelegate());
    // Create the Window. It will show itself after creation.
    CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));

    CefRefPtr<CefBrowser> browser = browser_view->GetBrowser();

    CefRefPtr<CefFrame> frame = browser->GetMainFrame();
    frame->LoadURL("https://www.bing.com/");
}

CefRefPtr<CefClient> SimpleApp::GetDefaultClient() {
    // Called when a new browser window is created via the Chrome runtime UI.
    return SimpleHandler::GetInstance();
}