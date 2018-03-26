// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "server/daemon/daemon.h"

#include "base/logging.h"
#include "base/memory/singleton.h"
#include "base/command_line.h"
#include "base/path_service.h"
#include "base/threading/platform_thread.h"

#include "base/bind.h"

#if !defined(OS_WIN)
#include <signal.h>
#if 0
#include "debugger/DbgLib.h"
#endif
#endif

namespace server {

base::MessageLoop* g_message_loop = NULL;

void OnShutdownDaemon(base::MessageLoop* message_loop) {
  if (message_loop) {
    message_loop->QuitNow();
  }
}

void DoShutdownDaemon(base::MessageLoop* message_loop) {
  if (message_loop) {
    message_loop->task_runner()->PostNonNestableTask(FROM_HERE,
      base::Bind(&OnShutdownDaemon, message_loop));
  }
}

#if defined OS_WIN
BOOL WINAPI ConsoleCtrlHandler(DWORD ctrl_type) {
  switch (ctrl_type) {
  case CTRL_C_EVENT:
  case CTRL_BREAK_EVENT:
  case CTRL_CLOSE_EVENT:
  case CTRL_SHUTDOWN_EVENT:
    DoShutdownDaemon(g_message_loop);
    return TRUE;
  default:
    return FALSE;
  }
}
#else
void SignalHandler(int signum) {
  switch (signum) {
  case SIGTERM:
  case SIGINT:
  case SIGHUP:
    DoShutdownDaemon(g_message_loop);
    break;
  }
}
#endif

// exception callback function
void ExceptionCallback(void*) {
}

Daemon::Daemon()
  : running_(false),
  message_loop_(NULL) {
}

Daemon::~Daemon() {
  if (message_loop_) {
    delete message_loop_;
    message_loop_ = NULL;
  }
}

int Daemon::LoadConfig(const base::FilePath& xml_ini_file) {
  return 0;
}

int Daemon::Initialize(int argc, char** argv) {
  return 0;
}

int Daemon::Run() {
  message_loop_->Run();
  return 0;
}

int Daemon::Run2() {
#if defined(OS_WIN)
  SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
  running_ = true;
#else
  signal(SIGPIPE, SIG_IGN);
  signal(SIGTERM, SignalHandler);
  signal(SIGINT, SignalHandler);
  signal(SIGHUP, SignalHandler);
  running_ = true;
#endif

  g_message_loop = message_loop();

  Run();

  return true;
}

int Daemon::Destroy() {
  return 0;
}

int Daemon::DoMain(int argc, char** argv) {
  base::CommandLine::Init(argc, argv);
  base::FilePath exe;
  PathService::Get(base::FILE_EXE, &exe);
  exe_path_ = exe.DirName();
  base::FilePath log_filename = exe.ReplaceExtension(FILE_PATH_LITERAL("log"));

  logging::LoggingSettings logging_settings;
  logging_settings.log_file = log_filename.value().c_str();
  logging_settings.lock_log = logging::LOCK_LOG_FILE;
  logging_settings.delete_old = logging::APPEND_TO_OLD_LOG_FILE;
  logging_settings.logging_dest = logging::LOG_TO_ALL;
  logging::InitLogging(logging_settings);

  // We want process and thread IDs because we may have multiple processes.
  // Note: temporarily enabled timestamps in an effort to catch bug 6361.
  logging::SetLogItems(false, true, true, true);

#if 0
  //#if !defined(OS_WIN)
    // enable exception handlers
  DbgLib::CDebugFx::SetExceptionHandler(true);
  // install an exception callback
  DbgLib::CDebugFx::SetExceptionCallback(ExceptionCallback, NULL);
#endif

  base::FilePath ini_filename = exe.ReplaceExtension(FILE_PATH_LITERAL("xml"));
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch("xml")) {
    ini_filename =
      exe.DirName().AppendASCII(command_line->GetSwitchValueASCII("xml"));
  }

  LOG(INFO) << "Load config " << ini_filename.AsUTF16Unsafe() << " ...";
  if (0 != LoadConfig(ini_filename)) {
    LOG(ERROR) << "Load config: " << ini_filename.AsUTF16Unsafe() << " error";
    return 2;
  }

  LOG(INFO) << "Initialize...";
  if (0 != Initialize(argc, argv)) {
    LOG(ERROR) << "error initialize";
    return 4;
  }

  LOG(INFO) << "Running...";
  Run2();

  LOG(INFO) << "Destroy...";
  Destroy();

  LOG(INFO) << "Shutdown...";
  return 0;
}
}
