/**
* xml_attributes.h
* DESCRIPTION:
*	参考CEGUI的部分代码
*
* Copyright (C) 2008, www.soucheng.com
* By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
*/

#ifndef SERVER_BASE_XML_XML_ATTRIBUTES_H_
#define SERVER_BASE_XML_XML_ATTRIBUTES_H_
#pragma once

#include <string>
#include <map>
#include <set>

#include "base/strings/string_piece.h"

namespace server {

class XMLAttributes {
public:
  XMLAttributes(void) {}
  virtual ~XMLAttributes(void) {}

  void Add(const base::StringPiece& attr_name, const base::StringPiece& attr_val);
  void Remove(const base::StringPiece& attr_name);
  bool Exists(const base::StringPiece& attr_name) const;
  size_t GetCount(void) const;

  bool GetName(size_t index, std::string* val) const;
  std::string GetName(size_t index) const;
  bool GetValue(size_t index, std::string* val) const;
  std::string GetValue2(size_t index) const;

  bool GetValue(const base::StringPiece& attr_name, std::string* val) const;
  bool GetValueAsBool(const base::StringPiece& attr_name, bool* val) const;
  bool GetValueAsInt(const base::StringPiece& attr_name, int* val) const;
  bool GetValueAsInt64(const base::StringPiece& attr_name, int64_t* val) const;
  bool GetValueAsFloat(const base::StringPiece& attr_name, float* val) const;

  std::string GetValueByName(const char* attr_name) const;

  void ToNames(std::set<base::StringPiece>* names) const;

  inline const std::map<base::StringPiece, base::StringPiece>& GetAttributes() const {
    return attrs_;
  }

protected:
  typedef std::map<base::StringPiece, base::StringPiece> AttributeMap;
  AttributeMap  attrs_;
};

}

#endif
