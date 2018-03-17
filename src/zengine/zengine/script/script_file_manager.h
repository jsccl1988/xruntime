// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 为了避免正在编辑文件、修改或删除时加载脚本文件，故采用外部程序主动通知来重新加载脚本
// 

#ifndef ZENGINE_SCRIPT_SCRIPT_FILE_MANAGER_H_
#define ZENGINE_SCRIPT_SCRIPT_FILE_MANAGER_H_
#pragma once

#include "base/memory/singleton.h"

#include "base/files/file_path.h"
#include "base/time/time.h"
#include "script/base/linked_map.h"

class ScriptManager;
class ScriptFileManager {
public:
  static ScriptFileManager* GetInstance() {
    return base::Singleton<ScriptFileManager>::get();
  }

  struct ScriptFileData {
    ScriptFileData() {
    }

    bool IsModified() {
      return last_modified_time != new_last_modified_time;
    }

    void SetLastModifiedTime(base::Time val) {
      last_modified_time = new_last_modified_time;
      new_last_modified_time = val;
    }

    base::Time last_modified_time;   // 文件最后修改时间
    base::Time new_last_modified_time;   // 文件最后修改时间
  };

  std::vector<base::FilePath>& GetWatcherFilePaths() {
    return watcher_file_paths_;
  }

  void RegisterScriptManager(ScriptManager* script_manager) {
    script_managers_.push_back(script_manager);
  }

  void Initialize(const std::vector<base::FilePath>& file_paths);
  void Destroy();

  script::linked_map<base::FilePath, ScriptFileData>& GetScriptDatas() {
    return script_datas_;
  }

private:
  friend struct base::DefaultSingletonTraits<ScriptFileManager>;

  ScriptFileManager() {
  }

  ~ScriptFileManager() {
    Destroy();
  }

  std::vector<base::FilePath> watcher_file_paths_;
  script::linked_map<base::FilePath, ScriptFileData> script_datas_;

  std::vector<ScriptManager*> script_managers_;
};

#endif
