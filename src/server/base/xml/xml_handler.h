/**
* xml_handler.h
* DESCRIPTION:
*	参考CEGUI的部分代码
*
* Copyright (C) 2007, www.soucheng.com
* By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
*/

#ifndef SERVER_BASE_XML_XML_HANDLER_H_
#define SERVER_BASE_XML_XML_HANDLER_H_
#pragma once

#include <string>

namespace server {

class XMLAttributes;
class XMLHandler {
public:
  XMLHandler(void) {}
  virtual ~XMLHandler(void) {}

  virtual bool ElementStart(const std::string& element, const XMLAttributes& attributes) { return true; }
  virtual bool ElementEnd(const std::string& element) { return true; }
  virtual bool Text(const std::string& text) { return true; }
};

}

#endif  //
