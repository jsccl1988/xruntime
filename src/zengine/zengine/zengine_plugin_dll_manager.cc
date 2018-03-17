// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/zengine/zengine_plugin_dll_manager.h"

#include "zengine/module/mod_net/module_net_dll.h"
#include "zengine/module/mod_db/module_db_dll.h"
#include "zengine/module/mod_xml/module_xml_dll.h"
#include "zengine/module/mod_console/module_console_dll.h"

namespace zengine {

void PluginDllManager::Initialize() {
  dll_funcs_.push_back(std::make_tuple(ModuleName_Net(),
    &DllStartModule_Net, &DllStopModule_Net));
  dll_funcs_.push_back(std::make_tuple(ModuleName_DB(),
    &DllStartModule_DB, &DllStopModule_DB));
  dll_funcs_.push_back(std::make_tuple(ModuleName_Xml(),
    &DllStartModule_Xml, &DllStopModule_Xml));
}

void PluginDllManager::DllStartModule(const std::string& module_name) {
  for (size_t i=0; i<dll_funcs_.size(); ++i) {
    if (std::get<0>(dll_funcs_[i]) == module_name) {
      std::get<1>(dll_funcs_[i])();
    }
  }
}

void PluginDllManager::DllStopModule(const std::string& module_name) {
  for (size_t i=0; i<dll_funcs_.size(); ++i) {
    if (std::get<0>(dll_funcs_[i]) == module_name) {
      std::get<2>(dll_funcs_[i])();
    }
  }
}
}
