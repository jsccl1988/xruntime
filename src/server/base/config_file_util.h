
// Copyright 2010, www.lelewan.com
// All rights reserved
//
// Author: wubenqi<wubenqi@caitong.net>, 2009-02-04
//

#ifndef BASE_CONFIG_FILE_UTIL_H_
#define BASE_CONFIG_FILE_UTIL_H_

#include <set>
#include <string>
#include <stdint.h>

#include "base/macros.h"
#include "base/stl_util.h"
#include "base/strings/string_piece.h"

namespace server {

class ConfigFile;

struct DBAddrInfo {
  DBAddrInfo() :
    port(0),
    min_conn_count(2),
    max_conn_count(5) {
  }

  bool ParseFromConnString(const base::StringPiece& conn_string);
  bool ParseFromConfigFile(const ConfigFile& config_file,
    const char* section_name);

  void PrintDebugString();

  void Destroy() {
    port = 0;
    min_conn_count = 2;
    max_conn_count = 5;

    STLClearObject(&host);
    STLClearObject(&user);
    STLClearObject(&passwd);
    STLClearObject(&db_name);
    STLClearObject(&db_type);
  }

  std::string host;
  int port;
  std::string user;
  std::string passwd;
  std::string db_name;
  std::string db_type;
  int min_conn_count;
  int max_conn_count;
};

struct IpAddrInfo {
  IpAddrInfo(const std::string& _addr, uint16_t _port)
    : addr(_addr)
    , port(_port) {
  }

  IpAddrInfo() {
    port = 0;
  }

  IpAddrInfo(const IpAddrInfo& other) {
    addr = other.addr;
    port = other.port;
  }

  void Destroy() {
    STLClearObject(&addr);
    port = 0;
  }

  bool ParseFromConfigFile(const ConfigFile& config_file,
    const char* section_name);

  inline IpAddrInfo& operator=(const IpAddrInfo& other) {
    addr = other.addr;
    port = other.port;
    return *this;
  }

  bool operator==(const IpAddrInfo& other) const {
    if (addr.empty() && port != 0) {
      return false;
    }
    return addr == other.addr && port == other.port;
  }

  // Allows GURL to used as a key in STL (for example, a std::set or std::map).
  bool operator < (const IpAddrInfo& other) const {
    if (addr < other.addr) {
      return true;
    }
    else if (addr == other.addr) {
      return port < other.port;
    }
    return false;
  }

  std::string addr; // IP地址
  uint16_t port; // 端口号
};

struct IpAddrInfo2 {
  IpAddrInfo2(const std::string& _addr, const std::string& _port)
    : addr(_addr)
    , port(_port) {
  }

  IpAddrInfo2() {
    // port = 0;
  }

  IpAddrInfo2(const IpAddrInfo2& other) {
    addr = other.addr;
    port = other.port;
  }

  void Destroy() {
    STLClearObject(&addr);
    STLClearObject(&port);
  }

  bool ParseFromConfigFile(const ConfigFile& config_file,
    const char* section_name);

  inline IpAddrInfo2& operator=(const IpAddrInfo2& other) {
    addr = other.addr;
    port = other.port;
    return *this;
  }

  bool operator==(const IpAddrInfo2& other) const {
    if (addr.empty() && port.empty()) {
      return false;
    }
    return addr == other.addr && port == other.port;
  }

  // Allows GURL to used as a key in STL (for example, a std::set or std::map).
  bool operator < (const IpAddrInfo2& other) const {
    if (addr < other.addr) {
      return true;
    }
    else if (addr == other.addr) {
      return port < other.port;
    }
    return false;
  }

  std::string addr; // IP地址
  std::string port; // 端口号
};

typedef std::set<std::string> HostList;

}

#endif

