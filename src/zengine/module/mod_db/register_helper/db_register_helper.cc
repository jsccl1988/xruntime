// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_db/register_helper/db_register_helper.h"

#include "script/luatinker/lua_tinker.h"

#include "zengine/zengine/zengine_context.h"

//#include "db/conn_pool_manager.h"
#include "zengine/module/mod_db/module_db_dll.h"
#include "zengine/module/mod_db/module_db_plugin.h"

CdbConnPoolManagerProxy* GetDBConnPoolMgrByInstanceName(const std::string& instance_name);
CdbConnPoolManagerProxy* GetDBConnPoolMgr();


namespace {

void Luabind_DB_Register(lua_State* l) {
  //lua_tinker::class_add<db::QueryAnswer>(l, "QueryAnswer");
  //lua_tinker::class_def<db::QueryAnswer>(l, "FetchRow", &db::QueryAnswer::FetchRow);
  //lua_tinker::class_def<db::QueryAnswer>(l, "PrintDebugFieldNames", &db::QueryAnswer::PrintDebugFieldNames);
  //lua_tinker::class_def<db::QueryAnswer>(l, "GetColumnName", &db::QueryAnswer::GetColumnName);
  //lua_tinker::class_def<db::QueryAnswer>(l, "GetColumnLength", (uint32_t(db::QueryAnswer::*)(uint32_t) const)&db::QueryAnswer::GetColumnLength);
  //lua_tinker::class_def<db::QueryAnswer>(l, "ColumnIsNull", (bool(db::QueryAnswer::*)(uint32_t) const)&db::QueryAnswer::ColumnIsNull);
  //lua_tinker::class_def<db::QueryAnswer>(l, "GetColumnValue", (std::string(db::QueryAnswer::*)(uint32_t) const)&db::QueryAnswer::GetColumnValue);
  //lua_tinker::class_def<db::QueryAnswer>(l, "GetColumnCount", &db::QueryAnswer::GetColumnCount);
  //lua_tinker::class_def<db::QueryAnswer>(l, "GetRowCount", &db::QueryAnswer::GetRowCount);

  lua_tinker::class_add<CdbConnPoolManagerProxy>(l, "CdbConnPoolManagerProxy");
  lua_tinker::class_def<CdbConnPoolManagerProxy>(l, "Query", &CdbConnPoolManagerProxy::Query);
  lua_tinker::class_def<CdbConnPoolManagerProxy>(l, "ExecuteInsertID", &CdbConnPoolManagerProxy::ExecuteInsertID);
  lua_tinker::class_def<CdbConnPoolManagerProxy>(l, "Execute", &CdbConnPoolManagerProxy::Execute);

  lua_tinker::def(l, "GetDBConnPoolMgrByInstanceName", &GetDBConnPoolMgrByInstanceName);
  lua_tinker::def(l, "GetDBConnPoolMgr", &GetDBConnPoolMgr);
}

}

//////////////////////////////////////////////////////////////////////////

#include "script/luabind_register_manager.h"

namespace zengine {

void DB_Register_Helper() {
  LuabindRegisterManager::GetInstance()->
    RegisterLuabindRegisterFunc(ModuleName_DB(), &Luabind_DB_Register);
}

}

