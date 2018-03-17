/**
 * xml_parser_module.h
 * DESCRIPTION:
 *	参考CEGUI的部分代码
 *
 * Copyright (C) 2007, www.soucheng.com
 * By Wu Benqi<wubenqi@youcity.com>, 2008-12-16
 */

#ifndef SERVER_BASE_XML_XML_PARSER_MODULE_H_
#define SERVER_BASE_XML_XML_PARSER_MODULE_H_
#pragma once

#include "server/base/xml/xml_parser.h"

server::XMLParser* CreateParser(int xml_type);
void DestroyParser(server::XMLParser* parser);

#endif
