// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZENGINE_ZENGINE_CONTEXT_H_
#define ZENGINE_ZENGINE_CONTEXT_H_
#pragma once

#include <string>
#include <vector>
#include "base/threading/platform_thread.h"
#include "server/base/timer_manager.h"

#include "net/base/io_buffer.h"

namespace {
  class MessageLoop;
}

class ScriptManager;
class ZEngineContextManager;

class ZEngineContext : public TimerManager::Delegate {
public:
  enum ZEngineContextType {
    kZEngineContextType_Invalid = 0,
    kZEngineContextType_Main = 1,
    kZEngineContextType_IO = 1,
    kZEngineContextType_ZEngine = 2
  };

  static const std::string kMainInstanceName;
  static const std::string kIOInstanceName;

  ZEngineContext(ZEngineContextManager* context_manager, int context_type
    , base::PlatformThreadId instance_id, const std::string& instance_name,
    base::MessageLoop* message_loop)
    : context_type_(context_type)
    , instance_id_(instance_id)
    , instance_name_(instance_name)
    , message_loop_(message_loop)
    , script_manager_(NULL)
    , timer_manager_(NULL)
    , context_manager_(context_manager) {
  }

  virtual ~ZEngineContext() {
  }

  bool Initialize();
  void Destroy();

  bool PostTaskByInstanceName(const std::string& instance_name,
    const std::string& task_data);
  bool PostTaskByInstanceID(base::PlatformThreadId instance_id,
    const std::string& task_data);
  bool PostTaskToIOThread(const std::string& task_data);
  void PostTaskToMainThread(const std::string& task_data);
  void PostTask(const std::string& task_data);

  void SetTimer(uint32_t timer_id, int tm);
  void KillTimer(uint32_t timer_id);

  int context_type() {
    return context_type_;
  }

  const std::string& instance_name() const {
    return instance_name_;
  }

  int instance_id() {
    return instance_id_;
  }

  base::MessageLoop* message_loop() {
    return message_loop_;
  }

  ScriptManager* script_manager() {
    return script_manager_;
  }

protected:
  virtual void OnTimer(uint32_t timer_id, int tm);
  void OnTaskDataReceived(std::string task_data);

private:
  int context_type_;
  std::string instance_name_;
  base::PlatformThreadId instance_id_;
  base::MessageLoop* message_loop_;
  ScriptManager* script_manager_;

  ZEngineContextManager* context_manager_;
  TimerManager* timer_manager_;
};

#endif
