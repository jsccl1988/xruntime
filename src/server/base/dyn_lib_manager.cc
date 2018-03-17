// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>


#include "server/base/dyn_lib_manager.h"
#include "server/base/dyn_lib.h"

namespace server {

DynLibManager::DynLibManager() {
}

DynLib* DynLibManager::Load(const std::string& filename) {
  DynLibList::iterator i = dylibs_.find(filename);
  if (i != dylibs_.end()) {
    return i->second;
  }
  else {
    DynLib* pLib = new DynLib(filename);
    pLib->Load();
    dylibs_[filename] = pLib;
    return pLib;
  }
}

void DynLibManager::Unload(DynLib* lib) {
  DynLibList::iterator i = dylibs_.find(lib->getName());
  if (i != dylibs_.end()) {
    dylibs_.erase(i);
  }
  lib->Unload();
  delete lib;
}

DynLibManager::~DynLibManager() {
  for (DynLibList::iterator it = dylibs_.begin(); it != dylibs_.end(); ++it) {
    it->second->Unload();
    delete it->second;
  }

  dylibs_.clear();
}
}
