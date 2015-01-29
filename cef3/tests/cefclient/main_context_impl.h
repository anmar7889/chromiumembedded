// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFCLIENT_MAIN_CONTEXT_IMPL_H_
#define CEF_TESTS_CEFCLIENT_MAIN_CONTEXT_IMPL_H_

#include "include/base/cef_scoped_ptr.h"
#include "include/base/cef_thread_checker.h"
#include "include/cef_app.h"
#include "include/cef_command_line.h"
#include "cefclient/main_context.h"

#if defined(OS_WIN) || defined(OS_LINUX)
#include "cefclient/root_window_manager.h"
#endif

namespace client {

// Used to store global context in the browser process.
class MainContextImpl : public MainContext {
 public:
  MainContextImpl(int argc,
                  const char* const* argv,
                  bool terminate_when_all_windows_closed);

  // MainContext members.
  std::string GetConsoleLogPath() OVERRIDE;
  std::string GetDownloadPath(const std::string& file_name) OVERRIDE;
  std::string GetAppWorkingDirectory() OVERRIDE;
  std::string GetMainURL() OVERRIDE;
  void PopulateSettings(CefSettings* settings) OVERRIDE;
  void PopulateBrowserSettings(CefBrowserSettings* settings) OVERRIDE;
#if defined(OS_WIN) || defined(OS_LINUX)
  RootWindowManager* GetRootWindowManager() OVERRIDE;
#endif

  // Initialize CEF and associated main context state. This method must be
  // called on the same thread that created this object.
  bool Initialize(const CefMainArgs& args,
                  const CefSettings& settings,
                  CefRefPtr<CefApp> application,
                  void* windows_sandbox_info);

  // Shut down CEF and associated context state. This method must be called on
  // the same thread that created this object.
  void Shutdown();

 private:
  // Allow deletion via scoped_ptr only.
  friend struct base::DefaultDeleter<MainContextImpl>;

  ~MainContextImpl();

  // Returns true if the context is in a valid state (initialized and not yet
  // shut down).
  bool InValidState() const {
    return initialized_ && !shutdown_;
  }

  const bool terminate_when_all_windows_closed_;

  // Track context state. Accessing these variables from multiple threads is
  // safe because only a single thread will exist at the time that they're set
  // (during context initialization and shutdown).
  bool initialized_;
  bool shutdown_;

  CefRefPtr<CefCommandLine> command_line_;
  std::string main_url_;

#if defined(OS_WIN) || defined(OS_LINUX)
  scoped_ptr<RootWindowManager> root_window_manager_;
#endif

  // Used to verify that methods are called on the correct thread.
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(MainContextImpl);
};

}  // namespace client

#endif  // CEF_TESTS_CEFCLIENT_MAIN_CONTEXT_IMPL_H_
