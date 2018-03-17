// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef MOD_XML_ZXML_WRAPPER_H_
#define MOD_XML_ZXML_WRAPPER_H_

#include "base/memory/singleton.h"
#include "server/base/xml/xml_attributes.h"
#include "server/base/xml/xml_handler.h"

#include "script/luatinker/lua_tinker.h"

namespace script {
class ScriptEngine;
}

namespace zengine {

class ZXmlWrapper :
  public server::XMLHandler {

public:
  ~ZXmlWrapper() {}

  static ZXmlWrapper* GetInstance() {
    return base::Singleton<ZXmlWrapper>::get();
  }

  void Initialize();

  bool DoParseXml(lua_tinker::table xml, const char* data);

  // from base::XMLHandler
  virtual bool ElementStart(const std::string& element,
    const server::XMLAttributes& attributes);
  virtual bool ElementEnd(const std::string& element);
  virtual bool Text(const std::string& text);

protected:
  friend struct base::DefaultSingletonTraits<ZXmlWrapper>;

  ZXmlWrapper() : script_(NULL) {
  }

  script::ScriptEngine* script_;
  std::unique_ptr<lua_tinker::table> table_;
};

}

#endif
