// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Edit by wubenqi
// 

#ifndef NET_MESSAGE_LOOP_MESSAGE_LOOP_FOR_NET_H_
#define NET_MESSAGE_LOOP_MESSAGE_LOOP_FOR_NET_H_

#include "base/message_loop/message_loop.h"

#include "net/message_loop/message_pump_net.h"

namespace net {

//-----------------------------------------------------------------------------
// MessageLoopForIO extends MessageLoop with methods that are particular to a
// MessageLoop instantiated with TYPE_IO.
//
// This class is typically used like so:
//   MessageLoopForIO::current()->...call some method...
//
class MessageLoopForNet : public base::MessageLoop {
 public:
  MessageLoopForNet() : MessageLoop(TYPE_CUSTOM) {
  }

  // Returns the MessageLoopForIO of the current thread.
  static MessageLoopForNet* current() {
    base::MessageLoop* loop = base::MessageLoop::current();
    DCHECK_EQ(base::MessageLoop::TYPE_CUSTOM, loop->type());
    return static_cast<MessageLoopForNet*>(loop);
  }

  static bool IsCurrent() {
    MessageLoop* loop = MessageLoop::current();
    return loop && loop->type() == MessageLoop::TYPE_CUSTOM;
  }

  typedef MessagePumpNet::Watcher Watcher;
  typedef MessagePumpNet::FileDescriptorWatcher
    FileDescriptorWatcher;
  typedef MessagePumpNet::IOObserver IOObserver;

  enum Mode {
    WATCH_READ = MessagePumpNet::WATCH_READ,
    WATCH_WRITE = MessagePumpNet::WATCH_WRITE,
    WATCH_READ_WRITE = MessagePumpNet::WATCH_READ_WRITE
  };

  void AddIOObserver(IOObserver* io_observer);
  void RemoveIOObserver(IOObserver* io_observer);

  bool WatchFileDescriptor(int fd,
    bool persistent,
    Mode mode,
    FileDescriptorWatcher *controller,
    Watcher *delegate);

};

// Do not add any member variables to MessageLoopForIO!  This is important b/c
// MessageLoopForIO is often allocated via MessageLoop(TYPE_IO).  Any extra
// data that you need should be stored on the MessageLoop's pump_ instance.
static_assert(sizeof(base::MessageLoop) == sizeof(net::MessageLoopForNet),
  " MessageLoopForNet should not have extra member variables");
}

#endif  // NET_MESSAGE_LOOP_MESSAGE_LOOP_FOR_NET_H_
