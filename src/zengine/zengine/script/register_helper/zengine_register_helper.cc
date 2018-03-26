// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/zengine/script/register_helper/zengine_register_helper.h"
#include "script/luatinker/lua_tinker.h"

#include "zengine/zengine/zengine_context.h"
#include "zengine/zengine/zengine_root.h"

namespace {

static const std::string kZEngineModuleName("mod_zengine");

bool CreateZEngineThread(const std::string& instance_name) {
  return zengine::Root::GetInstance()->CreateZEngineThread(instance_name);
}

void Luabind_ZEngine_Register(lua_State* l) {
    lua_tinker::class_add<ZEngineContext>(l, "ZEngineContext");

    lua_tinker::class_def<ZEngineContext>(
        l, "PostTaskByInstanceName", &ZEngineContext::PostTaskByInstanceName);
    lua_tinker::class_def<ZEngineContext>(
        l, "PostTaskByInstanceID", &ZEngineContext::PostTaskByInstanceID);
    lua_tinker::class_def<ZEngineContext>(
        l, "PostTaskToIOThread", &ZEngineContext::PostTaskToIOThread);
    lua_tinker::class_def<ZEngineContext>(
        l, "PostTaskToMainThread", &ZEngineContext::PostTaskToMainThread);
    lua_tinker::class_def<ZEngineContext>(
        l, "PostTask", &ZEngineContext::PostTask);
    lua_tinker::class_def<ZEngineContext>(
        l, "SetTimer", &ZEngineContext::SetTimer);
    lua_tinker::class_def<ZEngineContext>(
        l, "KillTimer", &ZEngineContext::KillTimer);
    lua_tinker::class_def<ZEngineContext>(
        l, "context_type", &ZEngineContext::context_type);
    lua_tinker::class_def<ZEngineContext>(
        l, "instance_name", &ZEngineContext::instance_name);
    lua_tinker::class_def<ZEngineContext>(
        l, "context_type", &ZEngineContext::instance_id);

    lua_tinker::def(l, "CreateZEngineThread", &CreateZEngineThread);
}

}

//////////////////////////////////////////////////////////////////////////

#include "script/luabind_register_manager.h"

namespace zengine {

void ZEngine_Register_Helper() {
  LuabindRegisterManager::GetInstance()->
    RegisterLuabindRegisterFunc(kZEngineModuleName, &Luabind_ZEngine_Register);
}

}
