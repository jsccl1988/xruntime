// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/http/http_server_request_info.h"

#include "base/strings/string_util.h"
#include "base/strings/string_tokenizer.h"

namespace net {

HttpServerRequestInfo::HttpServerRequestInfo() {}

HttpServerRequestInfo::~HttpServerRequestInfo() {}

std::string HttpServerRequestInfo::GetHeaderValue(
    const std::string& header_name) const {
  DCHECK_EQ(base::ToLowerASCII(header_name), header_name);
  HttpServerRequestInfo::HeadersMap::const_iterator it =
      headers.find(header_name);
  if (it != headers.end())
    return it->second;
  return std::string();
}

bool HttpServerRequestInfo::HasHeaderValue(
    const std::string& header_name,
    const std::string& header_value) const {
  DCHECK_EQ(base::ToLowerASCII(header_value), header_value);
  std::string complete_value = GetHeaderValue(header_name);
  complete_value = base::ToLowerASCII(complete_value);
  std::vector<std::string> value_items;
  base::StringTokenizer t(complete_value, ",");
  while (t.GetNext()) {
    std::string token = t.token();
    base::TrimString(token.c_str(), " \t", &token);
    if (token == header_value)
      return true;
  }
  for (std::vector<std::string>::iterator it = value_items.begin();
      it != value_items.end(); ++it) {

  }
  return false;
}

}  // namespace net
