// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
//	参考Ogre的部分代码
//

#ifdef WIN32
#  include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "server/base/exception.h"
#include "server/base/dyn_lib.h"

namespace server {

DynLib::DynLib(const std::string& name) {
  name_ = name;
  inst_ = NULL;
}

DynLib::~DynLib() {
}

void DynLib::Load() {
  std::string name = name_;
#if defined(OS_MACOSX)
  // dlopen() does not add .so to the filename, like windows does for .dll
  if (name.substr(name.length() - 6, 6) != ".dylib")
    name += ".dylib";
#elif defined(OS_LINUX)
  // dlopen() does not add .so to the filename, like windows does for .dll
  if (name.substr(name.length() - 3, 3) != ".so")
    name += ".so";
#endif

  inst_ = (DYNLIB_HANDLE)DYNLIB_LOAD(name.c_str());

  if (!inst_) {
    throw InternalErrorException(
      "Could not load dynamic library " + name_ +
      ".  System Error: " + DynlibError()
    );
  }
}

void DynLib::Unload() {
  if (DYNLIB_UNLOAD(inst_)) {
    throw InternalErrorException(
      "Could not unload dynamic library " + name_ +
      ".  System Error: " + DynlibError()
    );
  }

}

void* DynLib::GetSymbol(const std::string& strName) const throw() {
  return (void*)DYNLIB_GETSYM(inst_, strName.c_str());
}

std::string DynLib::DynlibError(void) {
#ifdef WIN32
  LPVOID lpMsgBuf;
  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    GetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR)&lpMsgBuf,
    0,
    NULL
  );
  std::string ret = (char*)lpMsgBuf;
  // Free the buffer.
  LocalFree(lpMsgBuf);
  return ret;
#else
  return std::string(dlerror());
#endif
}

}
