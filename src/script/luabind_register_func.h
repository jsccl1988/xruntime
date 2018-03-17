// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef SCRIPT_LUABIND_REGISTER_PB_H_
#define SCRIPT_LUABIND_REGISTER_PB_H_

#include <vector>
#include "script/base/linked_map.h"

struct lua_State;
typedef void (*LuabindRegister_Func)(lua_State* L);

typedef std::vector<LuabindRegister_Func> LuabindRegisterFuncList;
typedef script::linked_map<std::string, LuabindRegisterFuncList> LuabindRegisterFuncListMap;


#endif
