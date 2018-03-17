// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/zengine/script/script_file_manager.h"

#include "base/logging.h"
#include "base/files/file_util.h"
#include "base/files/file_enumerator.h"
#include "base/path_service.h"

namespace {
const int FILES_AND_DIRECTORIES =
        base::FileEnumerator::FILES |
        base::FileEnumerator::DIRECTORIES;
}

void ScriptFileManager::Initialize(const std::vector<base::FilePath>& file_paths) {
  // 保证只初始化一次
  if (!watcher_file_paths_.empty())
    return;

  base::FilePath exe;
  PathService::Get(base::FILE_EXE, &exe);

  base::FilePath file_path;
  for (size_t i=0; i<file_paths.size(); ++i) {
    file_path = exe.DirName().Append(file_paths[i]);
    if (base::DirectoryExists(file_path)) {
      base::FileEnumerator enumerator(file_path, true,
          FILES_AND_DIRECTORIES,
          FILE_PATH_LITERAL("*"));

      for (base::FilePath file2 = enumerator.Next();
        !file2.value().empty(); file2 = enumerator.Next()) {
        base::FilePath file;
        if (!base::NormalizeFilePath(file2, &file)) {
          file = file2;
        }

        if (file.Extension() == FILE_PATH_LITERAL(".lua")) {
          base::NormalizeFilePath(file, &file);
          if (script_datas_.find(file) == script_datas_.end()) {
            ScriptFileData script_fild_data;
            base::FileEnumerator::FileInfo file_info = enumerator.GetInfo();
            script_fild_data.SetLastModifiedTime(file_info.GetLastModifiedTime());
            script_datas_.insert(std::make_pair(file, script_fild_data));

            LOG(INFO) << "ScriptFileManager::Initialize - Ready load scipt file_path: "
              << file.AsUTF8Unsafe() << ".";
          }
        }
      }
    } else if (base::PathExists(file_path)) {
      base::FilePath file;
      if (!base::NormalizeFilePath(file_path, &file)) {
        file = file_paths[i];
      }
      if (file.Extension() == FILE_PATH_LITERAL(".lua")) {
        if (script_datas_.find(file) == script_datas_.end()) {
          base::File::Info file_info;
          if (base::GetFileInfo(file, &file_info)) {
            ScriptFileData script_fild_data;
            script_fild_data.SetLastModifiedTime(file_info.last_modified);
            script_datas_.insert(std::make_pair(file, script_fild_data));
            LOG(INFO) << "ScriptFileManager::Initialize - Ready load scipt file_path: "
              << file.AsUTF8Unsafe() << ".";
          }
        }
      }
    } else {
      LOG(ERROR) << "ScriptFileManager::Initialize - "
        << file_paths[i].AsUTF8Unsafe() << " is a invlaid file_path";
    }
  }

  watcher_file_paths_ = file_paths;
}

void ScriptFileManager::Destroy() {
  watcher_file_paths_.clear();
}