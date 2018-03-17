/**
 * expat_parser_module.cpp
 * DESCRIPTION:
 *	参考CEGUI的部分代码
 *
 * Copyright (C) 2007, www.soucheng.com
 * By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
 */


 //#define USE_EXPAT_PARSER
 //#define USE_MARKUPSTL_PARSER

#include "server/base/xml/xml_parser_module.h"

//#define USE_EXPAT_PARSER
#define USE_TINYXML_PARSER
//#define USE_RAPIDXML_XMLPARSER

#if defined(USE_EXPAT_PARSER)
#include "server/base/xml/expat_parser.h"
#endif

#if defined(USE_TINYXML_PARSER)
#include "server/base/xml/tinyxml_parser.h"
#endif

#if defined(USE_RAPIDXML_XMLPARSER)
#include "server/base/xml/rapidxml_parser.h"
#endif

#if !defined(USE_MARKUPSTL_PARSER) && !defined(USE_TINYXML_PARSER) && !defined(USE_MARKUPSTL_PARSER) && !defined(USE_RAPIDXML_XMLPARSER)
#include "server/base/xml/tinyxml_parser.h"
#endif

server::XMLParser* CreateParser(int xml_type) {
  server::XMLParser* xml_parser = NULL;
#if defined(USE_EXPAT_PARSER)
  if (xml_type == base::XMLParser::EXPAT_XMLPARSER) {
    xml_parser = new base::ExpatParser();
  }
#endif

#if defined(USE_TINYXML_PARSER)
  if (xml_type == server::XMLParser::TINYXML_XMLPARSER) {
    xml_parser = new server::TinyxmlParser();
  }
#endif

#if defined(USE_RAPIDXML_XMLPARSER)
  if (xml_type == base::XMLParser::RAPIDXML_XMLPARSER) {
    xml_parser = new base::RapidxmlParser();
  }
#endif

  if (!xml_parser) {
    xml_parser = new server::TinyxmlParser();
  }
  return xml_parser;
}

void DestroyParser(server::XMLParser* parser) {
  delete parser;
}
