// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef NETENGINE_ZNET_PACKET_H_
#define NETENGINE_ZNET_PACKET_H_

#include <stdint.h>

#include "base/memory/ref_counted.h"

#include "net/base/byte_stream.h"

namespace net {
  //接收处理数据包
class Packet :
  public base::RefCountedThreadSafe<Packet> {
public:
  static const uint32_t kMaxPacketSize = 2 * 1024 * 1024; // 2MB
  static const uint32_t kPacketHeaderSize = 8;
  static const uint32_t kPacketVersion = 0;
  const static uint32_t kPerPacketLen = 1024;

  // Packet();
  Packet(uint16_t cmd_type, uint32_t data_len);

  virtual ~Packet();

  inline int ParsePacketHeader() {
    uint16_t cmdType;
    uint32_t bodyLen;
    uint16_t version;

    version = (uint16_t)head_[0] << 8 | head_[1];
    cmdType = (uint16_t)head_[2] << 8 | head_[3];
    bodyLen = ((head_[4] & 0xFF) << 24)
      | ((head_[5] & 0xFF) << 16)
      | ((head_[6] & 0xFF) << 8)
      | (head_[7] & 0xFF);
    if (version != kPacketVersion
      || bodyLen > kMaxPacketSize) {
      return -1;
    }
    else if (bodyLen == 0) {
      return 1;
    }
    return 0;
  }

  inline uint16_t GetVersion() const {
    return (uint16_t)head_[0] << 8 | head_[1];
  }

  inline uint16_t GetCmdType() const {
    return (uint16_t)head_[2] << 8 | head_[3];
  }

  inline uint32_t GetBodyLength() const {
    return ((head_[4] & 0xFF) << 24)
      | ((head_[5] & 0xFF) << 16)
      | ((head_[6] & 0xFF) << 8)
      | (head_[7] & 0xFF
        );
  }

  inline const void* GetBodyData() const {
    return body_;
  }

  inline uint8_t* GetBodyData() {
    return body_;
  }

  inline uint8_t* GetHeadMutableBuffer() {
    return head_;
  }

  inline uint8_t* GetBodyMutableData() {
    return body_;
  }

  inline const uint8_t* GetRawdataConstBuffer() const {
    return head_;
  }

  inline uint32_t GetRawdataLength() const {
    return GetBodyLength() + kPacketHeaderSize;
  }

  void Release2() {
    if (ext_data_) {
      free(ext_data_);
      ext_data_ = NULL;

      head_ = data_;
      body_ = data_ + kPacketHeaderSize;
    }
  }

  Packet* Clone() const;

protected:
  friend class OutPacketStream;
  //此构造函数只能在OutByteStream里使用,其它地方使用会出问题
  Packet(uint16_t cmd_type, const void* data, uint32_t data_len);
  Packet(const void* data, uint32_t data_len);

  uint8_t* head_;
  uint8_t* body_;
  uint8_t* data_;
  uint8_t* ext_data_;

  DISALLOW_COPY_AND_ASSIGN(Packet);
};

typedef scoped_refptr<Packet> PacketPtr;

const PacketPtr& GetEmptyPacket();

class InPacketStream :
  public ByteStream {
public:
  InPacketStream(const PacketPtr& packet)
    : ByteStream(packet->GetBodyData(), packet->GetBodyLength()) {
  }

  virtual ~InPacketStream() {
  }
};

// 分配空间预留数据包头
class OutPacketStream :
  public ByteStream {
public:
  OutPacketStream(uint16_t cmd_type)
    : ByteStream() {
    Alloc(Packet::kPacketHeaderSize);
    is_transfered_ = false;
    cmd_type_ = cmd_type;
  }

  OutPacketStream(uint16_t cmd_type, uint32_t data_len)
    : ByteStream() {
    Alloc(data_len);
    is_transfered_ = false;
    cmd_type_ = cmd_type;
  }

  virtual ~OutPacketStream() {
    Free();
  }

  //注意,目前此函数只能调用一次
  PacketPtr GetPacket();

  inline void SetCmdType(uint16_t cmd_type) {
    cmd_type_ = cmd_type;
  }

  inline uint16_t GetCmdType() {
    return cmd_type_;
  }

protected:
  virtual void* Alloc(uint32_t new_len);
  virtual void  Free();

protected:
  char* data_;
  bool is_transfered_;
  uint16_t cmd_type_;
};
}

#endif //
