// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZENGINE_ZENGINE_CONTEXT_MANAGER_H_
#define ZENGINE_ZENGINE_CONTEXT_MANAGER_H_

#include <string>
#include <vector>
#include "base/threading/platform_thread.h"
#include "base/memory/singleton.h"

namespace base {
class MessageLoop;
}

class ZEngineContext;
class ZEngineContextManager {
public:
  static ZEngineContextManager* GetInstance() {
    return base::Singleton<ZEngineContextManager>::get();
  }

  ZEngineContext* CreateContext(int context_type,
    base::PlatformThreadId instance_id, const std::string& instance_name,
    base::MessageLoop* message_loop);

  void Destroy() {
    contexts_.clear();
  }

  ZEngineContext* LookupContext(const std::string& instance_name);
  ZEngineContext* LookupContext(base::PlatformThreadId instance_id);

  ZEngineContext* LookupMainContext();
  ZEngineContext* LookupIOContext();

private:
  ZEngineContextManager() {
  }
  ~ZEngineContextManager() {
  }

  friend class ZEngineContext;
  friend struct base::DefaultSingletonTraits<ZEngineContextManager>;

  void AddContext(ZEngineContext* context);
  void RemoveContext(ZEngineContext* context);

  std::vector<ZEngineContext*> contexts_;
};

#endif
