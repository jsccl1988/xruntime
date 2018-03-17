// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZENGINE_ZENGINE_DAEMON_H_
#define ZENGINE_ZENGINE_DAEMON_H_
#pragma once

#include <vector>
#include "base/memory/ref_counted.h"
#include "base/containers/hash_tables.h"

#include "server/base/config_file.h"
#include "server/daemon/daemon.h"

class ScriptManager;
class ZEngineThread;
class ZEngineContext;
class ZEngineContextManager;
class ZEngineDaemon :
  public server::Daemon {
public:
  ZEngineDaemon();
  virtual ~ZEngineDaemon();

protected:
  virtual int LoadConfig( const base::FilePath& xml_ini_file );
  virtual int Initialize( int argc, char** argv );
  virtual int Destroy();
  virtual int Run();

private:
  server::ConfigFile config_file_;
};

#endif
