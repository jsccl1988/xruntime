// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/zengine/script/script_manager.h"

#include "script/luabind_register_manager.h"

#include "zengine/zengine/script/script_file_manager.h"
#include "zengine/zengine/zengine_context.h"

ScriptManager::ScriptManager()
: script_file_manager_(NULL) {
}

ScriptManager::~ScriptManager() {
  Destroy();
}

bool ScriptManager::Initialize() {
  //app_name_ = app_name;
  script_engine_.Initialize();
  RegisterAll();

  script_file_manager_ = ScriptFileManager::GetInstance();
  script_file_manager_->RegisterScriptManager(this);

  LoadScripts();
  return true;
}

void ScriptManager::LoadScripts() {
  script::linked_map<base::FilePath, ScriptFileManager::ScriptFileData>::iterator it;
  script::linked_map<base::FilePath, ScriptFileManager::ScriptFileData>& script_datas =
    script_file_manager_->GetScriptDatas();
  for (it=script_datas.begin(); it!=script_datas.end(); ++it) {
    if (it->second.IsModified()) {
      script_engine_.DoFile(it->first.MaybeAsASCII());
    }
  }
}

void ScriptManager::RegisterAll() {
  LuabindRegisterManager::GetInstance()->
    RestiterAll(script_engine_.GetLuaState());
}

void ScriptManager::Destroy() {
  script_engine_.Destroy();
  script_file_manager_ = NULL;
}

//////////////////////////////////////////////////////////////////////////
int ScriptManager::ExeScript_MainInitialize() {
  int result = script_engine_.CallFunction<int>("MainInitialize");
  if (result!=0) {
    LOG(ERROR)
      << "ERROR: In main.lua, Execute MainInitialize() error, error_code = "
      << result;
  }
  return 0;
}

int ScriptManager::ExeScript_MainDestroy() {
  int result = script_engine_.CallFunction<int>("MainDestroy");
  if (result!=0) {
    LOG(ERROR)
      << "ERROR: In main.lua, Execute MainDestroy() error, error_code = "
      << result;
  }
  return 0;
}

int ScriptManager::ExeScript_OnThreadInitialize(ZEngineContext* context) {
  int result = script_engine_.CallFunction<int, ZEngineContext*>(
    "OnThreadInitialize", context);
  if (result!=0) {
    LOG(ERROR)
      << "ERROR: In main.lua, Execute OnThreadInitialize() error, error_code = "
      << result;
  }
  return 0;
}

int ScriptManager::ExeScript_OnThreadDestroy(ZEngineContext* context) {
  int result = script_engine_.CallFunction<int, ZEngineContext*>(
    "OnThreadDestroy", context);
  if (result!=0) {
    LOG(ERROR)
      << "ERROR: In main.lua, Execute OnThreadDestroy() error, error_code = "
      << result;
  }
  return 0;
}

int ScriptManager::ExeScript_OnTaskDataReceived(ZEngineContext* context,
  const std::string& task_data) {
  int result = script_engine_.CallFunction<int, ZEngineContext*, std::string>(
    "OnTaskDataReceived", context, task_data);
  if (result!=0) {
    LOG(ERROR)
      << "ERROR: In main.lua, Execute OnTaskDataReceived() error, error_code = "
      << result;
  }
  return 0;
}

int ScriptManager::ExeScript_OnTimer(ZEngineContext* context,
  uint32_t timer_id, int tm) {
  int result = script_engine_.CallFunction<int, ZEngineContext*, uint32_t, int>(
    "OnTimer", context, timer_id, tm);
  if (result!=0) {
    LOG(ERROR)
      << "ERROR: In main.lua, Execute OnTimer() error, error_code = " 
      << result;
  }
  return 0;
}
