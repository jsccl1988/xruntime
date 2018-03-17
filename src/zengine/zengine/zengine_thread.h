// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZENGINE_ZENGINE_THREAD_H_
#define ZENGINE_ZENGINE_THREAD_H_

#include "base/threading/thread.h"
#include "server/base/shared_ptr.h"

#include "net/base/io_buffer.h"
#include "zengine/zengine/script/script_manager.h"

class ZEngineContext;
class ZEngineThread : public base::Thread {
public:
  ZEngineThread(const std::string& thread_name);
  virtual ~ZEngineThread();

  void OnTaskDataReceived(shared_ptr<net::IOBuffer> task_data);

protected:
  // ´Óbase::Thread¼Ì³Ð
  virtual void Init();
  virtual void CleanUp();

private:
  ZEngineContext* context_;
};

#endif
