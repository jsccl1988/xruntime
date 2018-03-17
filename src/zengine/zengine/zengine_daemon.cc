// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/zengine/zengine_daemon.h"

#include "base/at_exit.h"
#include "base/sys_info.h"
#include "base/bind.h"
#include "base/stl_util.h"
#include "base/strings/sys_string_conversions.h"

#if defined(OS_WIN)
#include "net/base/winsock_init.h"
#endif

#include "net/message_loop/message_loop_for_net.h"

#include "zengine/zengine/zengine_root.h"
#include "zengine/zengine/script/script_file_manager.h"
#include "zengine/zengine/script/register_helper/base_register_helper.h"
#include "zengine/zengine/script/register_helper/zengine_register_helper.h"

ZEngineDaemon::ZEngineDaemon() 
  : Daemon() {
  message_loop_ = new base::MessageLoop(
    std::unique_ptr<base::MessagePump>(new net::MessagePumpNet()));
  zengine::Root::GetInstance();
}

ZEngineDaemon::~ZEngineDaemon() {
}

int ZEngineDaemon::LoadConfig( const base::FilePath& xml_ini_file ) {
  return config_file_.Initialize(
    base::SysWideToNativeMB(xml_ini_file.value()).c_str()) ? 0 : -1;
}

int ZEngineDaemon::Initialize( int argc, char** argv ) {  
  server::StringVector values 
    = config_file_.GetStringList("Scripts", "file_path");

  std::vector<base::FilePath> script_file_paths;
  for (size_t i=0; i<values.size(); ++i) {
    script_file_paths.push_back(
      base::FilePath::FromUTF8Unsafe(values.string_vector[i]));
  }
  ScriptFileManager::GetInstance()->Initialize(script_file_paths);
  
  zengine::Base_Register_Helper();
  zengine::ZEngine_Register_Helper();

  zengine::Root::GetInstance()->Initialize(&config_file_);

  return 0;
}

int ZEngineDaemon::Run() {
  zengine::Root::GetInstance()->Run();
  return 0;
}

int ZEngineDaemon::Destroy() {
  zengine::Root::GetInstance()->Shutdown();
  return 0;
}

int main(int argc, char* argv[]) {
  base::AtExitManager at_exit_manager;

#if defined(OS_WIN)
  net::EnsureWinsockInit();
#endif

  ZEngineDaemon daemon;
  return daemon.DoMain(argc, argv);
}
