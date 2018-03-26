// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZENGINE_SCRIPT_SCRIPT_MANAGER_H_
#define ZENGINE_SCRIPT_SCRIPT_MANAGER_H_

#include <vector>
#include <string>

#include "script/script_engine.h"

class ScriptFileManager;
class ZEngineContext;
class ScriptManager {
public:
  ScriptManager();
  ~ScriptManager();

  bool Initialize();
  void Destroy();

  script::ScriptEngine* GetScriptEngine() {
    return &script_engine_;
  }

  script::ScriptEngine& script_engine() {
    return script_engine_;
  }

  void DoWatchSignal();

  int ExeScript_MainInitialize();
  int ExeScript_MainDestroy();

  int ExeScript_OnThreadInitialize(ZEngineContext* context);
  int ExeScript_OnThreadDestroy(ZEngineContext* context);

  int ExeScript_OnTaskDataReceived(ZEngineContext* context,
    const std::string& task_data);
  int ExeScript_OnTimer(ZEngineContext* context, uint32_t timer_id, int tm);

private:
  void LoadScripts();
  void RegisterAll();

  void DoRefresh();

private:
  script::ScriptEngine script_engine_;
  std::vector<std::string> data_scripts_; 
  ScriptFileManager* script_file_manager_;
};

#endif

