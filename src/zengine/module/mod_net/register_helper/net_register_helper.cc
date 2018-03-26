// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_net/register_helper/net_register_helper.h"

#include "net/base/io_buffer.h"
#include "net/engine/io_handler.h"
#include "script/luatinker/lua_tinker.h"

#include "zengine/zengine/zengine_context.h"
#include "zengine/module/mod_net/module_net_dll.h"

namespace {

void Luabind_Net_Register(lua_State* l) {
  lua_tinker::class_add<base::StringPiece>(l, "StringPiece");

  lua_tinker::class_add<net::IOBuffer>(
    l, "IOBuffer");
  lua_tinker::class_def<net::IOBuffer>(
    l, "ReadableBytes", &net::IOBuffer::ReadableBytes);
  lua_tinker::class_def<net::IOBuffer>(
    l, "WritableBytes", &net::IOBuffer::WritableBytes);
  lua_tinker::class_def<net::IOBuffer>(
    l, "RetrieveAllAsString", &net::IOBuffer::RetrieveAllAsString);

  lua_tinker::class_add<net::IOHandler>(
    l, "IOHandler");
  lua_tinker::class_def<net::IOHandler>(
    l, "GetAddressString", &net::IOHandler::GetAddressString);
  lua_tinker::class_def<net::IOHandler>(
    l, "io_handler_id", &net::IOHandler::io_handler_id);
  lua_tinker::class_def<net::IOHandler>(
    l, "SendData", (bool(net::IOHandler::*)(net::IOBuffer*))&net::IOHandler::SendData);
  lua_tinker::class_def<net::IOHandler>(
    l, "SendString", &net::IOHandler::SendStringPiece);
}
}

//////////////////////////////////////////////////////////////////////////
#include "script/luabind_register_manager.h"

namespace zengine {

void Net_Register_Helper() {
  LuabindRegisterManager::GetInstance()->
    RegisterLuabindRegisterFunc(ModuleName_Net(), &Luabind_Net_Register);
}

}
