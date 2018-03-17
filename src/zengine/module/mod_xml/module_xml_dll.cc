// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_xml/module_xml_dll.h"

#include "base/logging.h"

#include "zengine/zengine/zengine_root.h"

#include "zengine/module/mod_xml/module_xml_plugin.h"

zengine::ModuleXmlPlugin* g_module_xml_plugin = NULL;

void DllStartModule_Xml(void) {
  g_module_xml_plugin = new zengine::ModuleXmlPlugin();
  zengine::Root::GetInstance()->InstallModule(g_module_xml_plugin);
}

void DllStopModule_Xml(void) {
  zengine::Root::GetInstance()->UninstallModule(g_module_xml_plugin);
  delete g_module_xml_plugin;
}

const std::string& ModuleName_Xml(void) {
  return zengine::ModuleXmlPlugin::GetModuleXmlName();
}
