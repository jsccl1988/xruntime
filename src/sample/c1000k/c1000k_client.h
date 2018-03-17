// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef C1000K_C1000K_CLIENT_H_
#define C1000K_C1000K_CLIENT_H_

#include <memory>

#include "base/memory/scoped_vector.h"
#include "base/files/file_path.h"

#include "net/codec/length_header/length_header_codec.h"
#include "net/engine/tcp_client.h"

#include "server/daemon/daemon.h"

class C1000kClient :
  public server::Daemon,
  public net::LengthHeaderCodec::Delegate {
public:
  C1000kClient();
  virtual ~C1000kClient();

protected:
  // server::Daemon
  virtual int LoadConfig( const base::FilePath& xml_ini_file );
  virtual int Initialize( int argc, char** argv );
  virtual int Destroy();

  // net::LengthHeaderCodec::Delegate
  virtual int OnLengthHeaderNewConnection(const net::IOHandlerPtr& ih);
  virtual int OnLengthHeaderDataReceived(const net::IOHandlerPtr& ih,
    const base::StringPiece& packet, base::Time receive_time);
  virtual int OnLengthHeaderConnectionClosed(const net::IOHandlerPtr& ih);

private:
  std::unique_ptr<net::LengthHeaderCodec> codec_;
  ScopedVector<net::TCPClient> conns_;
};

#endif // C1000K_C1000K_CLIENT_H_
