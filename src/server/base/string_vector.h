// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef SERVER_BASE_STRING_VECTOR_H_
#define SERVER_BASE_STRING_VECTOR_H_

#include <vector>
#include <string>

namespace server {

struct CStringVector {
  size_t size() const {
    return cstring_vector.size();
  }
  std::vector<const char*> cstring_vector;
};

struct StringVector {
  size_t size() const {
    return string_vector.size();
  }
  std::vector<std::string> string_vector;
};

}

#endif // SERVER_BASE_STRING_VECTOR_H_
