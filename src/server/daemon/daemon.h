// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 服务器基类,为服务器类提供了一个通用的流程:
// 包括读配置文件,初始化函数,销毁函数,以及循环驱动
//

#ifndef SERVER_DAEMON_H_
#define SERVER_DAEMON_H_
#pragma once

#include <string>

#include "base/message_loop/message_loop.h"

#include "base/files/file_path.h"

namespace server {

class Daemon {
public:
  Daemon();
  virtual ~Daemon();

  /**
    * 主函数,将执行文件的名字作为日志的标志打开日志;屏蔽SIGINT与SIGPIPE信号;
    * 并检查是否有"-xml"的默认参数,若存在,把它作为配置文件的名字,否则用执行文件的名字后缀
    * 上".xml"作为配置文件的名字,读取配置文件;依次执行初始化函数,循环驱动函数,与销毁函数,最后关闭日志
    * 其中每一步都记录到日志中.
    * @param argc 程序执行时所带的参数个数,包括执行文件
    * @param argv 程序执行时所带的参数,包括执行文件名
    * @return 成功则返回0
    * @see loadConfig(),initialize(),run(),destroy(),
    */
  virtual int DoMain(int argc, char** argv);

  void Quit() {
    running_ = false;
  }

  virtual base::MessageLoop* message_loop() {
    if (message_loop_ == NULL) {
      message_loop_ = new base::MessageLoop();
    }
    return message_loop_;
  }

  virtual int Run();

protected:
  /**
    * 读取配置文件,默认的配置文件名为argv[0].ini,与argv[0]在同一目录
    * 在initialize()前执行
    * @return 若读取不成功要中止程序 时则应该返回非0,此应用程序直接退出
    * 注意此时并不执行destroy()
    */
  virtual int LoadConfig(const base::FilePath& xml_ini_file);

  /**
    * 在LoadConfig()后的第一个函数,用于初始,如创建连接等等
    * @param argc 程序执行时所带的参数个数,包括执行文件
    * @param argv 程序执行时所带的参数,包括执行文件名
    * @return 若初始化不成功要中止程序 时则应该返回非0,此应用程序将调用destroy()后退出
    */
  virtual int Initialize(int argc, char** argv);

  /**
    * 清理函数,在应用程序即将退出前执行.用来执行释放在initialize()中申请的
    * 资源等工作.
    * @return 不成功则返回0
    */
  virtual int Destroy();

  virtual int DoLoop() {
    return 0;
  }

  int Run2();

  bool running_;
  base::MessageLoop* message_loop_;
  base::FilePath exe_path_;
};
}

#endif // SERVER_DAEMON_H_

