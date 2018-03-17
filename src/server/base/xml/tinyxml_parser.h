/**
* tinyxml_parser.h
* DESCRIPTION:
*	参考CEGUI的部分代码
*
* Copyright (C) 2007, www.soucheng.com
* By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
*/

#ifndef SERVER_BASE_XML_TINYXML_PARSER_H_
#define SERVER_BASE_XML_TINYXML_PARSER_H_
#pragma once

#include "server/base/xml/xml_parser.h"

namespace server {

class TinyxmlParser :
  public XMLParser {
public:
  TinyxmlParser(void);
  virtual ~TinyxmlParser(void);
  // Implementation of public abstract interface
  virtual bool ParseXMLData(XMLHandler& handler, const std::string &xml_text);
  virtual bool ParseXMLData(XMLHandler& handler, const char* xml_text, size_t xml_text_size);
  virtual bool ParseXMLFile(XMLHandler& handler, const std::string& filename);

protected:
  // Implementation of protected abstract interface.
  virtual bool InitialiseImpl(void);
  // Implementation of protected abstract interface.
  virtual void CleanupImpl(void);
};

}

#endif
