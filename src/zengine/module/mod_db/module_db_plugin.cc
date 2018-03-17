// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_db/module_db_plugin.h"

#include "base/stl_util.h"
//#include "db/base_database.h"
//#include "db/conn_pool_manager.h"

#include "server/base/config_file.h"

#include "zengine/module/mod_db/register_helper/db_register_helper.h"

namespace zengine {

const std::string kDBModuleName("mod_db");

const std::string& ModuleDBPlugin::GetModuleDBName() {
  return kDBModuleName;
}
const std::string& ModuleDBPlugin::GetPluginName() const {
  return kDBModuleName;
}

void ModuleDBPlugin::Install(const server::ConfigFile* config_file) {
  Plugin::Install(config_file);
  DB_Register_Helper();
}

void ModuleDBPlugin::Initialize() {
  const server::ConfigFile* config = config_file_;
  server::StringVector instances =
    config->GetStringList(kDBModuleName.c_str(), "instance_name");
  for (size_t i=0; i<instances.size(); ++i) {
    if (config->CheckBySection(instances.string_vector[i].c_str())) {
      //base::DBAddrInfo dbdi;
      //dbdi.ParseFromConfigFile(*config, instances.string_vector[i].c_str());

      //std::unique_ptr<db::CdbConnPoolManager> db_conn_pool_mgr(new db::CdbConnPoolManager());
      //bool inited =  db_conn_pool_mgr->Initialize(dbdi); 
      //if (inited) {
      //  CdbConnPoolManagerProxy* conn_pool = new CdbConnPoolManagerProxy(db_conn_pool_mgr.release());
      //  db_conn_pool_mgrs_.insert(std::make_pair(instances.string_vector[i], conn_pool));
      //}
    }
  }
}

void ModuleDBPlugin::Shutdown() {
  STLDeleteValues(&db_conn_pool_mgrs_);
}

void ModuleDBPlugin::Uninstall() {
}

CdbConnPoolManagerProxy* ModuleDBPlugin::GetDBConnPoolMgrByInstanceName(
  const std::string& instance_name) {
  CdbConnPoolManagerProxy* conn = NULL;
  linked_hash_map<std::string, CdbConnPoolManagerProxy*>::iterator it;
  for (it = db_conn_pool_mgrs_.begin(); it!=db_conn_pool_mgrs_.end(); ++it) {
    if (instance_name == it->first) {
      conn = it->second;
      break;
    }
  }
  return conn;
}

CdbConnPoolManagerProxy* ModuleDBPlugin::GetDBConnPoolMgr() {
  return db_conn_pool_mgrs_.empty()?NULL:db_conn_pool_mgrs_.begin()->second;
}

const std::string& ModuleDBPluginFactory::GetPluginName() const {
  return kDBModuleName;
}

Plugin* ModuleDBPluginFactory::CreateInstance() {
  return new ModuleDBPlugin();
}

void ModuleDBPluginFactory::DestroyInstance(Plugin* module) {
  ModuleDBPlugin* mod_db = reinterpret_cast<ModuleDBPlugin*>(module);
  if (mod_db) {
    delete mod_db;
    mod_db = NULL;
  }
}

}
