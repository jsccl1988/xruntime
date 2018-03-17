/**
* xml_lite.h
* DESCRIPTION:
*
* Copyright (C) 2007, www.soucheng.com
* By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
*/

#ifndef SERVER_BASE_XML_XML_LITE_H_
#define SERVER_BASE_XML_XML_LITE_H_
#pragma once

#include <string>

#include "base/macros.h"
#include "server/base/xml/xml_parser.h"

namespace server {

class XMLLite {
 public:
  explicit XMLLite(int xml_type = XMLParser::TINYXML_XMLPARSER);
  virtual ~XMLLite();

  XMLParser* GetXmlParser() {
    return xml_parser_;
  }

 private:
  XMLParser* xml_parser_;
  DISALLOW_COPY_AND_ASSIGN(XMLLite);
};

}

#endif
