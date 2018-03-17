// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
//	参考Ogre的部分代码
//

#ifndef SERVER_BASE_DYN_LIB_H_
#define SERVER_BASE_DYN_LIB_H_

#include <string>

#ifdef WIN32
#    define DYNLIB_HANDLE hInstance
#    define DYNLIB_LOAD( a ) LoadLibraryExA( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a ) !FreeLibrary( a )

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#else
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a ) dlclose( a )

#endif

namespace server {
class DynLib {
 public:
  DynLib( const std::string& name );
  ~DynLib();

  void Load();
  void Unload();
  const std::string& getName(void) const { 
    return name_; 
  }

  void* GetSymbol( const std::string& strName ) const throw();

protected:
  std::string name_;
  std::string DynlibError(void);

  DYNLIB_HANDLE inst_;
};

}

#endif  // SERVER_BASE_DYN_LIB_H_
