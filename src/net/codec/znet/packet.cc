// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "net/codec/znet/packet.h"

#include "base/logging.h"

namespace net {
const PacketPtr& GetEmptyPacket() {
  static PacketPtr kEmptyPacketPtr;
  return kEmptyPacketPtr;
}

Packet::Packet(uint16_t cmd_type, uint32_t data_len) {
  ext_data_ = NULL;
  data_ = (uint8_t*)malloc(data_len + kPacketHeaderSize);
  CHECK(data_ != NULL);
  head_ = data_;
  body_ = data_ + kPacketHeaderSize;

  head_[0] = (kPacketVersion >> 8) & 0xFF;
  head_[1] = kPacketVersion & 0xFF;
  head_[2] = (cmd_type >> 8) & 0xFF;
  head_[3] = cmd_type & 0xFF;
  head_[4] = (data_len >> 24) & 0xFF;
  head_[5] = (data_len >> 16) & 0xFF;
  head_[6] = (data_len >> 8) & 0xFF;
  head_[7] = data_len & 0xFF;
}

Packet::Packet(uint16_t cmd_type, const void* data, uint32_t data_len) {
  ext_data_ = NULL;
  data_ = (uint8_t*)data;
  CHECK(data_ != NULL);
  head_ = data_;
  body_ = data_ + kPacketHeaderSize;

  head_[0] = (kPacketVersion >> 8) & 0xFF;
  head_[1] = kPacketVersion & 0xFF;
  head_[2] = (cmd_type >> 8) & 0xFF;
  head_[3] = cmd_type & 0xFF;
  head_[4] = (data_len >> 24) & 0xFF;
  head_[5] = (data_len >> 16) & 0xFF;
  head_[6] = (data_len >> 8) & 0xFF;
  head_[7] = data_len & 0xFF;
}

Packet::Packet(const void* data, uint32_t data_len) {
  CHECK(data != NULL);
  ext_data_ = NULL;
  data_ = (uint8_t*)data;
  head_ = data_;
  body_ = data_ + kPacketHeaderSize;
}

Packet::~Packet() {
  Release2();
  free(data_);
}

Packet* Packet::Clone() const {
  int len = kPacketHeaderSize + GetBodyLength();
  uint8_t *data = (uint8_t*)malloc(len);
  CHECK(data != NULL);
  memcpy(data, head_, len);
  Packet* p = new Packet(data, len);
  CHECK(p != NULL);
  return p;
}

//////////////////////////////////////////////////////////////////////////

void* OutPacketStream::Alloc(uint32_t new_len) {
  if (failed_) return 0;
  if (new_len > max_len_) {
    // determine new buffer size
    uint32_t dwNewBufferSize = max_len_;
    while (dwNewBufferSize < new_len) {
      dwNewBufferSize += Packet::kPacketHeaderSize;
    }

    // allocate new buffer
    if (buffer_ == 0) {
      data_ = (char *)malloc(dwNewBufferSize + Packet::kPacketHeaderSize);
    }
    else {
      data_ = (char *)realloc(data_, dwNewBufferSize + Packet::kPacketHeaderSize);
    }
    CHECK(data_);
    if (0 == data_) {
      failed_ = 1;
      return 0;
    }
    max_len_ = dwNewBufferSize - Packet::kPacketHeaderSize;
    buffer_ = data_ + Packet::kPacketHeaderSize;
  }
  return data_;
}

void  OutPacketStream::Free() {
  if (is_new_) {
    if (data_)
      free(data_);
    data_ = NULL;
    buffer_ = NULL;
  }
}

//todo: 
PacketPtr OutPacketStream::GetPacket() {
  CHECK(!is_transfered_) << "GetPacket() only invoke once!!!!!";
  if (!is_transfered_) {
    is_transfered_ = true;
    is_new_ = false;
  }
  return PacketPtr(new Packet(cmd_type_, data_, Tell()));
}


PacketPtr CreatePacketData(uint16_t cmd_type, const void* data,
  uint32_t data_len) {
  PacketPtr packet(new Packet(cmd_type, data_len));
  memcpy(packet->GetBodyData(), data, data_len);
  return packet;
}
}
