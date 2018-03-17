// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef SERVER_BASE_TIMER_MANAGER_H_
#define SERVER_BASE_TIMER_MANAGER_H_

#include <memory>

#include "base/containers/hash_tables.h"
#include "base/message_loop/message_loop.h"
#include "base/timer/timer.h"

class TimerManager {
public:
  class Delegate {
  public:
    virtual ~Delegate() {}
    virtual void OnTimer(uint32_t timer_id, int tm) {}
  };

  TimerManager(Delegate* delegate, base::MessageLoop* message_loop)
    : message_loop_(message_loop)
    , delegate_(delegate) {
  }

  ~TimerManager() {
    Destroy();
  }

  void Destroy();

  void SetTimer(uint32_t timer_id, int tm);
  void KillTimer(uint32_t timer_id);

private:
  void HandleTimeout(unsigned int timer_id, int tm);
  typedef std::shared_ptr<base::Timer> TimerPtr;

  base::MessageLoop* message_loop_;
  typedef base::hash_map<uint32_t, TimerPtr> TimerMap;
  TimerMap timers_;
  Delegate* delegate_;
};

#endif // SERVER_BASE_TIMER_MANAGER_H_
