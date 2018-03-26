// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef SERVER_BASE_CONFIG_FILE_XML_HANDLER_H_
#define SERVER_BASE_CONFIG_FILE_XML_HANDLER_H_
#pragma once

#include "server/base/xml/xml_attributes.h"
#include "server/base/xml/xml_handler.h"

#include "server/base/config_file.h"

namespace server {

class ConfigFileXmlHandler :
  public server::XMLHandler {
public:
  ConfigFileXmlHandler(ConfigFile::SectionMap& config_map);
  virtual ~ConfigFileXmlHandler() {}

  // À´×Ôserver::XMLHandler
  virtual bool ElementStart(const std::string& element,
    const XMLAttributes& attributes);
  virtual bool ElementEnd(const std::string& element);
  virtual bool Text(const std::string& text);

private:
  ConfigFile::SectionMap& config_map_;

  ConfigFile::SectionMap::iterator current_it_;
  ConfigFile::KeyValuePair* current_key_value_pair_;
  std::string current_element_;
};

}

#endif

