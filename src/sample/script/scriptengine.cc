// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// Lua½Å±¾ÒýÇæ
//

#include <iostream>
#include <memory>

#include "base/command_line.h"
#include "base/at_exit.h"
#include "base/logging.h"
#include "base/md5.h"
#include "base/strings/sys_string_conversions.h"

#include "script/script_engine.h"

std::string MD5String(const std::string& str) {
  base::MD5Digest digest;
  base::MD5Sum(str.c_str(), str.length(), &digest);
  return base::MD5DigestToBase16(digest);
}

lua_tinker::table Table(lua_tinker::table t) {
  return t;
}

void Luabind_Base_Register(lua_State* l) {
  lua_tinker::def(l, "MD5String", &MD5String);
  lua_tinker::def(l, "UTF8ToNativeMB", &base::SysWideToNativeMB);
}

class T {
public:
  T() {
    std::cout << "T::T()" << std::endl;
  }
  ~T() {
    std::cout << "T::~T()" << std::endl;
  }
  void Print() {
    std::cout << "T::Print()" << std::endl;
  }
};

std::shared_ptr<T> CreateTSharedPtr() {
  return std::shared_ptr<T>(new T());
}

T CreateT() {
  return T();
}

void CppRegister(script::ScriptEngine* script_engine) {
  script_engine->RegisterClass<T>("T");
  script_engine->RegisterClassFuncnction<T>("Print", &T::Print);

  script_engine->RegisterClass<std::shared_ptr<T> >("SharedPtrT");
  script_engine->RegisterClassFuncnction<std::shared_ptr<T> >("Get", &std::shared_ptr<T>::get);

  script_engine->RegisterFunction("MD5String", &MD5String);
  script_engine->RegisterFunction("Table", &Table);

  script_engine->RegisterFunction("CreateTSharedPtr", &CreateTSharedPtr);
  script_engine->RegisterFunction("CreateTTest", &CreateT);
}

int main(int argc, char* argv[]) {
  base::AtExitManager at_exit;

  base::CommandLine::Init(argc, argv);

  logging::LoggingSettings logging_settings;
  logging_settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;
  logging::InitLogging(logging_settings);
  logging::SetLogItems(false, true, true, true);

  if (argc != 2) {
    LOG(ERROR) << "Need lua file!!!";
    return -1;
  }

  script::ScriptEngine script_engine;
  script_engine.Initialize();
  CppRegister(&script_engine);

  script_engine.DoFile(argv[1]);
  script_engine.CallFunction<int>("DoMain");
  script_engine.Destroy();

  return 0;
}