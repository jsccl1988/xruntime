// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "net/base/byte_stream.h"

namespace net {

ByteStream::ByteStream(void)
  : is_new_(true)
  , max_len_(0)
  , data_len_(0)
  , current_pos_(0)
  , failed_(0)
  , buffer_(0) {
}

ByteStream::ByteStream(const void* buffer, uint32_t data_len)
  : buffer_((char*)buffer)
  , is_new_(false)
  , max_len_(data_len)
  , data_len_(data_len)
  , current_pos_(0)
  , failed_(0) {
}

ByteStream::~ByteStream() {
  Free();
}

//////////////////////////////////////////////////////////
void* ByteStream::Alloc(uint32_t new_len) {
  if (failed_) return 0;
  if (!is_new_) {
    failed_ = 1;
    return 0;
  }
  if (new_len > max_len_) {
    // determine new buffer size
    uint32_t new_buffer_size = max_len_;
    while (new_buffer_size < new_len) new_buffer_size += 4096;

    // allocate new buffer
    if (buffer_ == 0) buffer_ = (char *)malloc(new_buffer_size);
    else	buffer_ = (char *)realloc(buffer_, new_buffer_size);
    if (0 == buffer_) {
      failed_ = 1;
      return 0;
    }
    //LOG_ASSERT(buffer_!=NULL);
    max_len_ = new_buffer_size;
  }
  return buffer_;
}

void ByteStream::Free() {
  if (is_new_) {
    free(buffer_);
    buffer_ = NULL;
  }
}

//////////////////////////////////////////////////////////////////////////
int32_t ByteStream::Seek(uint32_t pos) const {
  if (pos > max_len_) {
    return -1;
  }

  uint32_t lOld = current_pos_;
  current_pos_ = pos;
  failed_ = 0;

  return lOld;
}

uint32_t ByteStream::Tell() const {
  return current_pos_;
}

int32_t ByteStream::Skip(uint32_t pos) const {
  if (current_pos_ + pos > max_len_) {
    return -1;
  }

  current_pos_ += pos;
  failed_ = 0;

  return 0;
}

bool ByteStream::Fail() const {
  return 0 != failed_;
}

const char* ByteStream::Data() const {
  return buffer_;
}

char* ByteStream::MutableData(void) {
  return buffer_;
}

uint32_t ByteStream::Length() const {
  return data_len_;
}

//////////////////////////////////////////////////////////////////////////
int32_t ByteStream::ReadRawData(void* data, uint32_t data_len) const {
  if (failed_) {
    return -1;
  }

  if (current_pos_ + data_len > max_len_) {
    failed_ = 1;
    return -1;
  }

  if (data_len == 0) {
    return 0;
  }

  memcpy(data, buffer_ + current_pos_, data_len);
  current_pos_ += data_len;

  return 0;
}

int32_t ByteStream::ReadString(char* s, uint32_t data_len) const {
  uint8_t ch[4];
  uint32_t l;
  if (0 != ReadRawData(ch, sizeof(ch))) {
    return -1;
  }
  else {
    l = ((ch[0] & 0xFF) << 24) | ((ch[1] & 0xFF) << 16) | ((ch[2] & 0xFF) << 8) | (ch[3] & 0xFF);
    if (l > data_len) {
      l = data_len;
      s[l - 1] = '\0';
    }
  }
  return ReadRawData(s, l);
}

int32_t ByteStream::ReadString(std::string& str) const {
  uint8_t ch[4];
  uint32_t l;
  if (0 != ReadRawData(ch, sizeof(ch))) {
    return -1;
  }
  else {
    l = ((ch[0] & 0xFF) << 24) | ((ch[1] & 0xFF) << 16) | ((ch[2] & 0xFF) << 8) | (ch[3] & 0xFF);
  }

  if (current_pos_ + l > max_len_) {
    failed_ = 1;
    return -1;
  }
  str.clear();
  // str.append(buffer_ + current_pos_, 0, l);
  str.append(buffer_ + current_pos_, l);
  current_pos_ += l;
  return 0;
}

const ByteStream& ByteStream::operator >> (std::string& str) const {
  ReadString(str);
  return *this;
}

const ByteStream& ByteStream::operator >> (bool& b) const {
  if (current_pos_ + sizeof(char) > max_len_) {
    failed_ = 1;
  }
  else {
    b = buffer_[current_pos_++] ? true : false;
  }
  return *this;
}

const ByteStream& ByteStream::operator >> (uint8_t& ch) const {
  if (current_pos_ + sizeof(ch) > max_len_) {
    failed_ = 1;
  }
  else {
    ch = buffer_[current_pos_++];
  }
  return *this;
}

const ByteStream& ByteStream::operator >> (char& ch) const {
  if (current_pos_ + sizeof(ch) > max_len_) {
    failed_ = 1;
  }
  else {
    ch = buffer_[current_pos_++];
  }
  return *this;
}

const ByteStream& ByteStream::operator >> (int16_t& s) const {
  uint8_t ch[2];
  if (0 == ReadRawData(ch, sizeof(ch))) {
    s = (int16_t)((ch[0] & 0xFF) << 8) | (ch[1] & 0xFF);
  }
  return *this;
}

const ByteStream& ByteStream::operator >> (uint16_t& s) const {
  uint8_t ch[2];
  if (0 == ReadRawData(ch, sizeof(ch))) {
    s = (uint16_t)((ch[0] & 0xFF) << 8) | (ch[1] & 0xFF);
  }
  return *this;
}

const ByteStream& ByteStream::operator >> (int32_t& l) const {
  uint8_t ch[4];
  if (0 == ReadRawData(ch, sizeof(ch))) {
    l = (int32_t)((ch[0] & 0xFF) << 24) | ((ch[1] & 0xFF) << 16) | ((ch[2] & 0xFF) << 8) | (ch[3] & 0xFF);
  }
  return *this;
}

const ByteStream& ByteStream::operator >> (uint32_t& l) const {
  uint8_t ch[4];
  if (0 == ReadRawData(ch, sizeof(ch))) {
    l = (uint32_t)((ch[0] & 0xFF) << 24) | ((ch[1] & 0xFF) << 16) | ((ch[2] & 0xFF) << 8) | (ch[3] & 0xFF);
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////
int32_t ByteStream::WriteRawData(const void* data, uint32_t data_len) {
  if (failed_) {
    return -1;
  }

  if (data_len == 0) {
    return 0;
  }

  if (current_pos_ + data_len > max_len_) {
    if (is_new_) {
      if (0 == Alloc(current_pos_ + data_len)) {
        return -1;
      }
    }
    else {
      return -1;
    }
  }

  memcpy(buffer_ + current_pos_, data, data_len);
  current_pos_ += data_len;

  if (data_len_ < current_pos_) {
    data_len_ = current_pos_;
  }

  return 0;
}

int32_t ByteStream::WriteString(const char* s) {
  uint32_t len = strlen(s);

  uint8_t ch[4];
  ch[0] = (len >> 24) & 0xff;
  ch[1] = (len >> 16) & 0xff;
  ch[2] = (len >> 8) & 0xff;
  ch[3] = len & 0xff;

  if (0 != WriteRawData(ch, sizeof(ch))) {
    return -1;
  }

  return WriteRawData(s, len);
}

int32_t ByteStream::WriteString(const std::string& str) {
  uint32_t	len = str.length();

  uint8_t ch[4];
  ch[0] = (len >> 24) & 0xff;
  ch[1] = (len >> 16) & 0xff;
  ch[2] = (len >> 8) & 0xff;
  ch[3] = len & 0xff;

  if (0 != WriteRawData(ch, sizeof(ch))) {
    return -1;
  }

  return WriteRawData(str.c_str(), len);
}

ByteStream& ByteStream::operator << (const std::string& str) {
  WriteString(str);
  return *this;
}

ByteStream& ByteStream::operator << (bool b) {
  uint8_t ch = b ? 1 : 0;
  WriteRawData(&ch, sizeof(ch));
  return *this;
}

ByteStream& ByteStream::operator << (uint8_t ch) {
  WriteRawData(&ch, sizeof(uint8_t));
  return *this;
}

ByteStream& ByteStream::operator << (char ch) {
  WriteRawData(&ch, sizeof(char));
  return *this;
}

ByteStream& ByteStream::operator << (int16_t s) {
  uint8_t ch[2];
  ch[0] = (s >> 8) & 0xff;
  ch[1] = s & 0xff;
  WriteRawData(ch, sizeof(ch));
  return *this;
}

ByteStream& ByteStream::operator << (uint16_t s) {
  uint8_t ch[2];
  ch[0] = (s >> 8) & 0xff;
  ch[1] = s & 0xff;
  WriteRawData(ch, sizeof(ch));
  return *this;
}

ByteStream& ByteStream::operator << (int32_t l) {
  uint8_t ch[4];
  ch[0] = (l >> 24) & 0xff;
  ch[1] = (l >> 16) & 0xff;
  ch[2] = (l >> 8) & 0xff;
  ch[3] = l & 0xff;
  WriteRawData(ch, sizeof(ch));
  return *this;
}

ByteStream& ByteStream::operator << (uint32_t l) {
  uint8_t ch[4];
  ch[0] = (l >> 24) & 0xff;
  ch[1] = (l >> 16) & 0xff;
  ch[2] = (l >> 8) & 0xff;
  ch[3] = l & 0xff;
  WriteRawData(ch, sizeof(ch));
  return *this;
}

}
