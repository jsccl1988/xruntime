// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Edit by wubenqi
// 

#include "net/message_loop/message_loop_for_net.h"

namespace net {

namespace {

typedef MessagePumpNet MessagePumpForNet;

MessagePumpForNet* ToPumpIO(base::MessagePump* pump) {
  return static_cast<MessagePumpForNet*>(pump);
}

}

//------------------------------------------------------------------------------
// MessageLoopForIO

void MessageLoopForNet::AddIOObserver(
    MessageLoopForNet::IOObserver* io_observer) {
  ToPumpIO(pump_.get())->AddIOObserver(io_observer);
}

void MessageLoopForNet::RemoveIOObserver(
    MessageLoopForNet::IOObserver* io_observer) {
  ToPumpIO(pump_.get())->RemoveIOObserver(io_observer);
}

bool MessageLoopForNet::WatchFileDescriptor(int fd,
                                           bool persistent,
                                           Mode mode,
                                           FileDescriptorWatcher *controller,
                                           Watcher *delegate) {
  return ToPumpIO(pump_.get())->WatchFileDescriptor(
      fd,
      persistent,
      mode,
      controller,
      delegate);
}

}
