// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zengine/module/mod_net/module_net_plugin.h"

#include "base/logging.h"
#include "base/stl_util.h"

#if defined(OS_WIN)
#include "net/base/winsock_init.h"
#endif

#include "server/base/config_file.h"
#include "zengine/zengine/zengine_context.h"
#include "zengine/zengine/zengine_context_manager.h"
#include "zengine/zengine/script/script_manager.h"

#include "zengine/module/mod_net/register_helper/net_register_helper.h"

namespace zengine {

const std::string kNetModuleName("mod_net");

const std::string& ModuleNetPlugin::GetModuleNetName() {
  return kNetModuleName;
}

ModuleNetPlugin::ModuleNetPlugin() {
}

ModuleNetPlugin::~ModuleNetPlugin() {
  STLDeleteElements(&clients_);
  STLDeleteElements(&servers_);
}

const std::string& ModuleNetPlugin::GetPluginName() const {
  return kNetModuleName;
}

void ModuleNetPlugin::Install(const server::ConfigFile* config_file) {
  Plugin::Install(config_file);

#if defined(OS_WIN)
  net::EnsureWinsockInit();
#endif
  Net_Register_Helper();
}

void ModuleNetPlugin::Initialize() {
  server::StringVector instances = config_file_->
    GetStringList(kNetModuleName.c_str(), "instance_name");
  for (size_t i=0; i<instances.size(); ++i) {
    if (config_file_->CheckBySection(instances.string_vector[i].c_str())) {
      CommNodeInfo* comm_node2 = new CommNodeInfo();
      CommNodeInfo& comm_node = *comm_node2;
      const char* val = NULL;
      comm_node.instance_name = instances.string_vector[i];
      val = config_file_->GetString(instances.string_vector[i].c_str(), "net_type");
      if (!val) {
        LOG(ERROR) << "ModuleNetPlugin::Initialize - CommNodeInfo:"
          << instances.string_vector[i] << ":host is empty.";
        break;
      }
      comm_node.net_type = val;
      if (!comm_node.CheckNetType()) {
        LOG(ERROR) << "ModuleNet2Plugin::Initialize - net_type:"
          << val << "is invalid, shuold is " << CommNodeInfo::kNetType_TCPAcceptor
          << " or " << CommNodeInfo::kNetType_TCPConnector;
      }

      val = config_file_->GetString(instances.string_vector[i].c_str(), "addr_info");
      if (!val) { LOG(ERROR) << "ModuleNet2Plugin::Initialize - CommNodeInfo:"
        << instances.string_vector[i] << ":user is empty."; break; }
      comm_node.addr = val;
      size_t pos = comm_node.addr.find_first_of(':');
      if (pos==std::string::npos) {
        LOG(ERROR) << "ModuleNet2Plugin::Initialize - addr_info:" <<
          val << "is invalid, not sep char ':'";
      }
      comm_node.port = comm_node.addr.substr(pos+1, comm_node.addr.length() - pos - 1);
      comm_node.addr = comm_node.addr.substr(0, pos);
      comm_node.reconnected_timeout =
        config_file_->GetInt(instances.string_vector[i].c_str(), "reconnected_time", 10);

      // Ö±½ÓÁ¬°É
      comm_nodes_.push_back(comm_node2);
      if (comm_node.NetTypeIsTCPConnector()) {
        ZNetTCPClient* client = new ZNetTCPClient();
        client->Connect(comm_node);
        clients_.push_back(client);
      } else {
        std::unique_ptr<ZNetTCPServer> server(new ZNetTCPServer());
        if(!server->Create(comm_node)) {
          LOG(ERROR) << "ModuleNet2Plugin::Initialize - Create TCPAcceptor server "
            << comm_node.addr << ":" << comm_node.port << " error!";
        } else {
          servers_.push_back(server.release());
        }
      }
    }
  }
}

void ModuleNetPlugin::Shutdown() {
}

void ModuleNetPlugin::Uninstall() {
}

const std::string& ModuleNetPluginFactory::GetPluginName() const {
  return kNetModuleName;
}

Plugin* ModuleNetPluginFactory::CreateInstance() {
  return new ModuleNetPlugin();
}

void ModuleNetPluginFactory::DestroyInstance(Plugin* module) {
  ModuleNetPlugin* net_db = reinterpret_cast<ModuleNetPlugin*>(module);
  if (net_db) {
    delete net_db;
    net_db = NULL;
  }
}
}
