// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>

#ifndef SERVER_BASE_DYN_LIB_MANAGER_H_
#define SERVER_BASE_DYN_LIB_MANAGER_H_

#include <string>
#include <map>
#include "base/memory/singleton.h"

namespace server {

class DynLib;
class DynLibManager {
public:
  static DynLibManager* GetInstance() {
    return base::Singleton<DynLibManager>::get();
  }

  DynLib* Load(const std::string& filename);

  void Unload(DynLib* lib);

protected:
  friend struct base::DefaultSingletonTraits<DynLibManager>;

  DynLibManager();
  virtual ~DynLibManager();

  typedef std::map<std::string, DynLib*> DynLibList;
  DynLibList dylibs_;
};

}

#endif
