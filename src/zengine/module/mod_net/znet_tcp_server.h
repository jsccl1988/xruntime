// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef MOD_NET_ZNET_TCP_SERVER_H_
#define MOD_NET_ZNET_TCP_SERVER_H_

#include "server/base/shared_ptr.h"
#include "net/engine/tcp_server.h"

#include "zengine/module/mod_net/comm_node_info.h"
#include "zengine/module/mod_net/znet_handler_context.h"

namespace script {
class ScriptEngine;
}

namespace zengine {

class ZNetTCPServer : public net::IOHandler::Delegate {
public:
  ZNetTCPServer() 
    : script_(NULL) {}
  virtual ~ZNetTCPServer() {}

  bool Create(const CommNodeInfo& comm_node_info);

  // From IOHandler::Delegate
  virtual int  OnNewConnection(const net::IOHandlerPtr& ih);
  virtual int  OnDataReceived(const net::IOHandlerPtr& ih,
    net::IOBuffer* data, base::Time receive_time);
  virtual int  OnConnectionClosed(const net::IOHandlerPtr& ih);

private:
  shared_ptr<net::TCPServer> server_;
  shared_ptr<ZNetHandlerContext> znet_handler_context_;
  script::ScriptEngine* script_;
};

}

#endif

