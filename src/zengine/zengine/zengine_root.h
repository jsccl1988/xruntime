// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZENGINE_ZENGINE_ROOT_H_
#define ZENGINE_ZENGINE_ROOT_H_

#include <vector>

#include "base/memory/singleton.h"
#include "base/files/file_path.h"

#include "server/base/shared_ptr.h"
#include "server/base/config_file.h"

#include "zengine/zengine/zengine_plugin.h"

namespace base {
class MessageLoop;
}

namespace net {
class ConfigFile;
}

class ZEngineThread;
class ZEngineContext;
namespace zengine {

class Root {
public:
  typedef std::vector<Plugin*> ModuleInstanceList;

  static Root* GetInstance() {
    return base::Singleton<Root>::get();
  }

  void Initialize(const server::ConfigFile* config);
  void Shutdown();

  bool IsInitialized(void) const { return is_initialized_; }

  void Run();

  void OnCreate();
  void OnDestroy();

  bool CreateZEngineThread(const std::string& instance_name);

  void LoadModules(const std::vector<std::string>& module_names);
  void InitializeModules();
  void ShutdownModules();
  void UnloadModules();
  void LoadModule(const std::string& module_name);
  void UnloadModule(const std::string& module_name);
  void InstallModule(Plugin* module);
  void UninstallModule(Plugin* module);

  const ModuleInstanceList& GetInstalledModules() const { return modules_; }

private:
  friend struct base::DefaultSingletonTraits<Root>;
  void DoShutdown();

  Root();
  virtual ~Root();

  ModuleInstanceList modules_;
  bool is_initialized_;

  typedef base::hash_map<std::string, shared_ptr<ZEngineThread> > ZEngineThreadMap;
  ZEngineThreadMap zengine_threads_;
  ZEngineContext* context_;

  base::MessageLoop* message_loop_;

  DISALLOW_COPY_AND_ASSIGN(Root);

  const server::ConfigFile* config_file_;
};

}

#endif
