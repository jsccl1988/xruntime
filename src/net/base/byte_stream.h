// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef NET_BASE_BYTE_STREAM_H_
#define NET_BASE_BYTE_STREAM_H_

#include <stdint.h>

#include <string>

namespace net {

class ByteStream {
public:
  // Flag values
  // enum Mode { store = 0, load = 1}; // 储存（写档）或载出（读档）
  // 或内存储存（内存写档）或从内存载出（内存读档）
  /**
    * 构造用于写入的ByteStream对象,可写入的最大字节数
    * @param dataLen 数据的最大长度
    */
  ByteStream();

  /**
    * 构造用于读出的ByteStream对象,假定pBuffer中有dataLen长度的数据
    * 任何对ByteStream对象的更改将影响给定的pBuffer中的数据
    * @param pBuffer 数据,应确保至少有dataLen长度
    * @param dataLen 数据长度
    */
  ByteStream(const void* buffer, uint32_t data_len);

  virtual ~ByteStream(void);

public:
  /**
    * 将内部指针定位到某一位置
    * @param pos 将内部指针定位到的位置,此位置相对于开始位置(0)
    * @return 成功返回当前内部指针指的位置,否则返回-1
    */
  int32_t Seek(uint32_t pos) const;

  /**
    * 返回内部指针所指的位置
    * @return 不成功返回-1
    */
  uint32_t Tell(void) const;

  /**
    * 跳过几个字节
    * @param pos 要跳过的字节数
    * @return 成功返回0
    */
  int32_t Skip(uint32_t pos) const;

  /**
    * 判断operator << 与operator >>操作 是否成功
    * @return 若不成功,则返回true
    */
  bool Fail(void) const;

  /**
    * 返回底层的缓冲区指针
    */
  const char* Data(void) const;
  char* MutableData(void);

  /**
    * 返回底层的数据的长度
    */
  uint32_t Length(void) const;

  /**
    * 读出几个字节
    * @param pdata 存放读出的数据,应当确保此指针至少能够容纳dataLen个字节
    * @param dataLen 要读出的字节数
    * @return 成功返回0
    */
  int32_t ReadRawData(void* data, uint32_t data_len) const;

  /**
    * 写入几个字节
    * @param pdata 要写入的数据,应当确保此指针至少拥有dataLen个字节
    * @param dataLen 要写入的字节数
    * @return 成功返回0
    */
  int32_t WriteRawData(const void* data, uint32_t data_len);

  /**
    * 读出一个字符串(以'\0'结尾)
    * @param pdata 存放读出的字符串,应当确保此指针至少能够容纳dataLen个字节
    * @param dataLen 要读出的字节数,包括结尾字符'\0'
    * @return 成功返回0
    */
  int32_t ReadString(char* s, uint32_t data_len) const;
  int32_t ReadString(std::string& str) const;
  const ByteStream& operator >> (std::string& str) const;

  /**
    * 写入一个字符串(以'\0'结尾)
    * @param pdata 要写入的字符串
    * @return 成功返回0
    */
  int32_t WriteString(const char* s);
  int32_t WriteString(const std::string& str);
  ByteStream& operator << (const std::string& str);

  /**
    * 写入一个bool数据
    * @param b 要写入的bool
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (bool b);

  /**
    * 写入一个char据
    * @param ch 要写入的ch
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (char ch);

  /**
    * 写入一个uint8_t据
    * @param ch 要写入的uint8_t
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (uint8_t ch);

  /**
    * 写入一个int16_t据
    * @param s 要写入的int16_t
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (int16_t s);

  /**
    * 写入一个uint16_t据
    * @param s 要写入的uint16_t
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (uint16_t s);

  /**
    * 写入一个int32_t据
    * @param l 要写入的int32_t
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (int32_t l);

  /**
    * 写入一个uint32_t据
    * @param l 要写入的uint32_t
    * @return 不成功,则fail() == true
    */
  ByteStream& operator << (uint32_t l);

  /**
    * 写入一个int32_t
    * @param l 存放读出的int32_t
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (bool& b) const;

  /**
    * 读出一个char
    * @param ch 存放读出的char
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (char& ch) const;

  /**
    * 读出一个uint8_t
    * @param ch 存放读出的uint8_t
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (uint8_t& ch) const;

  /**
    * 读出一个int16_t
    * @param s 存放读出的int16_t
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (int16_t& s) const;

  /**
    * 读出一个uint16_t
    * @param s 存放读出的uint16_t
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (uint16_t& s) const;

  /**
    * 读出一个int32_t
    * @param l 存放读出的int32_t
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (int32_t& l) const;

  /**
    * 读出一个int32_t
    * @param l 存放读出的int32_t
    * @return 不成功,则fail() == true
    */
  const ByteStream& operator >> (uint32_t& l) const;

  operator bool() const {
    return 0 == failed_;
  }
  bool operator!() const {
    return 0 != failed_;
  }


protected:
  /** 防止拷贝构造操作 */
  ByteStream(const ByteStream& s);
  /** 防止赋值操作 */
  ByteStream& operator= (const ByteStream& s);

protected:
  virtual void* Alloc(uint32_t dwNewLen);
  virtual void  Free();

protected:
  char* buffer_; /**< 实际用于读写的缓冲区 */
  bool is_new_; /**< buffer_是否是用动态分配的 */
  uint32_t max_len_; /**< 缓冲区的最大长度 */
  uint32_t data_len_; /**< 缓冲区中的数据长度 */
  mutable uint32_t current_pos_; /**< 缓冲区中读写的当前位置 */
  mutable uint32_t failed_; /**< 指示读写操作是否成功 */
};

} // namespace net
#endif // NET_BASE_BYTE_STREAM_H_

