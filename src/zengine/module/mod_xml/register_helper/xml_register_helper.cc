// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_xml/register_helper/xml_register_helper.h"

#include "script/luatinker/lua_tinker.h"

#include "zengine/zengine/zengine_context.h"
#include "zengine/module/mod_xml/module_xml_dll.h"
#include "zengine/module/mod_xml/zxml_wrapper.h"

namespace {

bool DoParseXml(lua_tinker::table xml, const char* data) {
  return zengine::ZXmlWrapper::GetInstance()->DoParseXml(xml, data);
}

void Luabind_Xml_Register(lua_State* L) {
  lua_tinker::class_add<server::XMLAttributes>(L, "XMLAttributes");

  lua_tinker::class_def<server::XMLAttributes>(L, "GetName", (std::string(server::XMLAttributes::*)(size_t) const)&server::XMLAttributes::GetName);
  lua_tinker::class_def<server::XMLAttributes>(L, "GetValue", &server::XMLAttributes::GetValue2);
  lua_tinker::class_def<server::XMLAttributes>(L, "GetCount", &server::XMLAttributes::GetCount);
  lua_tinker::class_def<server::XMLAttributes>(L, "GetValueByName", &server::XMLAttributes::GetValueByName);

  lua_tinker::def(L, "DoParseXml", &DoParseXml);
}

}

//////////////////////////////////////////////////////////////////////////

#include "script/luabind_register_manager.h"
namespace zengine {

void Xml_Register_Helper() {
  LuabindRegisterManager::GetInstance()->
    RegisterLuabindRegisterFunc(ModuleName_Xml(), &Luabind_Xml_Register);
}

}
