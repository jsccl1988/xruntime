/**
* xml_attributes.cpp
* DESCRIPTION:
*	≤ŒøºCEGUIµƒ≤ø∑÷¥˙¬Î
*
* Copyright (C) 2008, www.soucheng.com
* By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
*/

#include "server/base/xml/xml_attributes.h"

#include <sstream>
#include <iterator>

#include "base/strings/string_util.h"
#include "base/logging.h"
#include "base/strings/string_number_conversions.h"


namespace server {

void XMLAttributes::Add(const base::StringPiece& attr_name,
  const base::StringPiece& attr_value) {
  attrs_[attr_name] = attr_value;
}

void XMLAttributes::Remove(const base::StringPiece& attr_name) {
  AttributeMap::iterator pos = attrs_.find(attr_name);

  if (pos != attrs_.end()) {
    attrs_.erase(pos);
  }
}

bool XMLAttributes::Exists(const base::StringPiece& attr_name) const {
  return attrs_.find(attr_name) != attrs_.end();
}

size_t XMLAttributes::GetCount(void) const {
  return attrs_.size();
}

bool XMLAttributes::GetName(size_t index, std::string* val) const {
  if (index >= attrs_.size()) {
    return false;
  }

  AttributeMap::const_iterator iter = attrs_.begin();
  std::advance(iter, index);
  *val = iter->first.as_string();
  return true;
}

std::string XMLAttributes::GetName(size_t index) const {
  if (index >= attrs_.size()) {
    return "";
  }

  AttributeMap::const_iterator iter = attrs_.begin();
  std::advance(iter, index);
  return iter->first.as_string();
}

bool XMLAttributes::GetValue(size_t index, std::string* val) const {
  if (index >= attrs_.size()) {
    return false;
  }

  AttributeMap::const_iterator iter = attrs_.begin();
  std::advance(iter, index);

  *val = iter->second.as_string();
  return true;
}

std::string XMLAttributes::GetValue2(size_t index) const {
  std::string v;
  GetValue(index, &v);
  return v;
}


bool XMLAttributes::GetValue(const base::StringPiece& attr_name,
  std::string* val) const {
  AttributeMap::const_iterator pos = attrs_.find(attr_name);

  if (pos != attrs_.end()) {
    *val = pos->second.as_string();
    return true;
  } else {
    return false;
  }
}

std::string XMLAttributes::GetValueByName(const char* attr_name) const {
  std::string v;
  GetValue(attr_name, &v);
  return v;
}

bool XMLAttributes::GetValueAsBool(const base::StringPiece& attr_name, bool* val) const {
  AttributeMap::const_iterator pos = attrs_.find(attr_name);
  if (pos == attrs_.end()) {
    return false;
  }

  if (pos->second == "false" || pos->second == "0") {
    *val = false;
    return true;
  }
  else if (pos->second == "true" || pos->second == "1") {
    *val = true;
    return true;
  }
  else {
    LOG(ERROR) << "XMLAttributes::getValueAsInteger - failed to convert attribute '"
      << attr_name << "' with value '" << pos->second << "' to bool.";
    return false;
  }
}

bool XMLAttributes::GetValueAsInt(const base::StringPiece& attr_name, int* val) const {
  AttributeMap::const_iterator pos = attrs_.find(attr_name);
  if (pos == attrs_.end()) {
    return false;
  }

  if (!base::StringToInt(pos->second, val)) {
    LOG(ERROR) << "XMLAttributes::GetValueAsInt - failed to convert attribute '"
      << attr_name << "' with value '" << pos->second << "' to integer.";
    return false;
  }
  return true;
}

bool XMLAttributes::GetValueAsInt64(const base::StringPiece& attr_name, int64_t* val) const {
  AttributeMap::const_iterator pos = attrs_.find(attr_name);
  if (pos == attrs_.end()) {
    return false;
  }

  if (!base::StringToInt64(pos->second, val)) {
    LOG(ERROR) << "XMLAttributes::GetValueAsInt64 - failed to convert attribute '"
      << attr_name << "' with value '" << pos->second << "' to integer.";
    return false;
  }
  return true;
}

bool XMLAttributes::GetValueAsFloat(const base::StringPiece& attr_name, float* val) const {
  AttributeMap::const_iterator pos = attrs_.find(attr_name);

  if (pos == attrs_.end()) {
    return false;
  }

  double tmp_val;

  if (!base::StringToDouble(pos->second.as_string(), &tmp_val)) {
    LOG(ERROR) << "XMLAttributes::GetValueAsFloat - failed to convert attribute '"
      << attr_name << "' with value '" << pos->second << "' to integer.";
    return false;
  }

  *val = static_cast<float>(tmp_val);
  return true;
}

void XMLAttributes::ToNames(std::set<base::StringPiece>* names) const {
  AttributeMap::const_iterator it = attrs_.begin();
  for (; it != attrs_.end(); ++it) {
    names->insert(it->first);
  }
}

} // End of  base namespace section

