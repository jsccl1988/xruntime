// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_net/module_net_dll.h"

#include "base/logging.h"

#include "zengine/zengine/zengine_root.h"
#include "zengine/module/mod_net/module_net_plugin.h"

zengine::ModuleNetPlugin* g_module_net_plugin = NULL;

void DllStartModule_Net(void) {
  g_module_net_plugin = new zengine::ModuleNetPlugin();
  zengine::Root::GetInstance()->InstallModule(g_module_net_plugin);
}

void DllStopModule_Net(void) {
  zengine::Root::GetInstance()->UninstallModule(g_module_net_plugin);
  delete g_module_net_plugin;
  g_module_net_plugin = NULL;
}

const std::string& ModuleName_Net(void) {
  return zengine::ModuleNetPlugin::GetModuleNetName();
}
